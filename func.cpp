#include "func.h"

string LoadShader(const char* filename)
{
    string res;
    ifstream file(filename, ios::in);
    if (file.is_open()) {
        stringstream sstr; // Буфер для чтения
        sstr << file.rdbuf(); // Считываем файл
        res = sstr.str();   //Получаем строку из буфера
        file.close();       //Закрываем файл
    }
    return res;
}

void getViewMatrix(GLFWwindow* window, mat4* ViewMatrix)
{
    int windowWidth, windowHeight; // параметры окна
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    double mouseX, mouseY; // позиция курсора
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // угол по оси XZ. Чем больше значение, тем больше камера смотрит "вправо"
    horAngleRad += mouseSpeed * (windowWidth / 2 - mouseX);
    // угол по оси Y. Чем больше значение, тем больше камера смотрит "вверх"
    verAngleRad += mouseSpeed * (windowHeight / 2 - mouseY);

    glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);

    // определяет направление, в которо смотрит камера (а еще для движения вперед-назад)
    vec3 direction(
        cos(verAngleRad) * sin(horAngleRad),
        sin(verAngleRad),
        cos(verAngleRad) * cos(horAngleRad));

    // определяет угол, на который поднята или опущена камера(а еще для движения влево-вправо)
    vec3 right = vec3(
        sin(horAngleRad - PI / 2.0f),
        0,
        cos(horAngleRad - PI / 2.0f));

    // определяет вертикальную ось (по факту ось Y)
    vec3 up = cross(right, direction);

    // управление камерой
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) // вверх
        CamPosition.y += CamSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)  // вниз
        CamPosition.y -= CamSpeed;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // вперед
        CamPosition += direction * CamSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // назад
        CamPosition -= direction * CamSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // влево
        CamPosition -= right * CamSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // вправо
        CamPosition += right * CamSpeed;

    *ViewMatrix = lookAt(CamPosition, CamPosition + direction, up); // меняем саму матрицу
}

GLFWwindow* InitMain()
{
    setlocale(LC_ALL, "Russian"); // для вывода в консоль кириллицы

    GLFWwindow* window = nullptr;
    if (!glfwInit()) {  // инициализация glfw
        cerr << "ERROR: could not start GLFW3\n";
        exit(-1);
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, "skeleton party", NULL, NULL); // инициализация окна
    if (!window) { glfwTerminate(); exit(-1); }

    glfwSetKeyCallback(window, key_callback); // привязываем функция обработчика нажатий
    glfwMakeContextCurrent(window); // делаем активным созданное окна

    glewExperimental = GL_TRUE; // инициализация glew

    if (glewInit() != GLEW_OK) { cerr << "ERROR: could not start GLEW\n"; return nullptr; }

    return window;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case GLFW_KEY_ESCAPE: // закрываем окно (esc)
        if (action == GLFW_PRESS)
            glfwTerminate();
        exit(1);
        break;

    case GLFW_KEY_Z: // анимация поворота (z)
        if (action == GLFW_PRESS)
            isRotateSkull = !isRotateSkull;
        break;

    case GLFW_KEY_X: // анимация движения (x)
        if (action == GLFW_PRESS)
            isMoveSkulls = !isMoveSkulls;
        break;

    case GLFW_KEY_UP: // движение объекта вперед (стрелка вверх)
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            objPosition.z -= objShift;
        break;

    case GLFW_KEY_RIGHT: // движение объекта вправо (стрелка вправо)
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            objPosition.x += objShift;
        break;

    case GLFW_KEY_DOWN: // движение объекта назад (стрелка вниз)
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            objPosition.z += objShift;
        break;

    case GLFW_KEY_LEFT: // движение объекта влево (стрелка влево)
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            objPosition.x -= objShift;
        break;

    case GLFW_KEY_MINUS: // движение объекта вверх (-)
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            objPosition.y -= objShift;
        break;

    case GLFW_KEY_EQUAL: // движение объекта вниз (=)
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            objPosition.y += objShift;
        break;

    case GLFW_KEY_Q: // Уменьшение яркости (q)
        if ((action == GLFW_PRESS || action == GLFW_REPEAT) &&
            lights.pointLights[0].diffuse.x > 0)
            lights.pointLights[0].diffuse -= vec3(0.03f);
        break;

    case GLFW_KEY_E: // Увеличение яркости (e)
        if ((action == GLFW_PRESS || action == GLFW_REPEAT) &&
            lights.pointLights[0].diffuse.x < 3)
            lights.pointLights[0].diffuse += vec3(0.03f);
        break;

    }
}

bool loadOBJ(const char* path, // путь к файлу модели
    vector<vec3>& outVertices, // выходной вектор с вершинными координатами 
    vector<vec2>& outTextures,  // выходной вектор с текстурными координатами 
    vector<vec3>& outNormals // выходной вектор с координатами нормалей 
)
{
    //Временные массивы для хранения индексов и значений из файла
    vector<unsigned int> vertexIndices, vtIndices, normalIndices;
    vector<vec3> temp_vertices;
    vector<vec2> temp_textures;
    vector<vec3> temp_normals;

    //Строка для хранения токенов из файла
    string buf;
    //Буфер, хранящий содержимое файла
    stringstream sstr;
    //Переменная для корректной работы с неизвестным числом вершин в грани
    bool cont = false;

    //Считывание файла
    ifstream file(path, ios::in);
    if (file.is_open()) {
        sstr << file.rdbuf();
        file.close();
    }
    else
        return false;

    //Очистка выходных массивов
    outNormals.clear();
    outVertices.clear();
    outTextures.clear();

    //Попытка считать токен из файла
    while (cont || sstr >> buf)
    {
        cont = false;

        //Обработка координат
        if (buf == "v") {
            vec3 vertex;
            sstr >> vertex.x;
            sstr >> vertex.y;
            sstr >> vertex.z;
            temp_vertices.push_back(vertex);
        }
        //Обработка текстурных координат
        else if (buf == "vt") {
            vec2 texture;
            sstr >> texture.x;
            sstr >> texture.y;
            temp_textures.push_back(texture);
        }
        //Обработка нормалей
        else if (buf == "vn") {
            vec3 normal;
            sstr >> normal.x;
            sstr >> normal.y;
            sstr >> normal.z;
            temp_normals.push_back(normal);
        }
        //Обработка граней
        else if (buf == "f") {
            //Временные массивы для хранения информации о грани
            vector<string> vertexes;
            vector<int> vertindexes;
            while (!cont)
            {
                //Считывается токен
                sstr >> buf;
                //Если токен содержит данные о вершине - она записывается в массив
                if (buf.find('/') != string::npos)
                    vertexes.push_back(buf);
                //Если токен - начало следующей строки, он сохраняется и начинается обработка грани
                else
                {
                    //Для каждой из сохранённых вершин производится парсинг данных
                    for (string vert : vertexes)
                    {
                        replace(vert.begin(), vert.end(), '/', ' ');
                        stringstream tmpstream(vert);
                        int v, vt, n;
                        tmpstream >> v;
                        tmpstream >> vt;
                        tmpstream >> n;
                        //Индексы заносятся в временный массив
                        vertindexes.push_back(v);
                        vertindexes.push_back(vt);
                        vertindexes.push_back(n);
                    }
                    //Первые три вершины заносятся вмассивы индексов
                    for (int i = 0; i < 3; i++)
                    {
                        vertexIndices.push_back(vertindexes[i * 3 + 0]);
                        vtIndices.push_back(vertindexes[i * 3 + 1]);
                        normalIndices.push_back(vertindexes[i * 3 + 2]);
                    }
                    //Дальше сложнее - если ещё остались вершины, надо и их занести
                    //Но надо преобразовать из веера треугольников в набор треугольников
                    size_t tmpsize = vertexes.size();
                    if (tmpsize > 3)
                    {
                        //Для каждой из вершин добавляются три вершины, образующие треугольник
                        for (int i = 3; i < tmpsize; i++)
                        {
                            vertexIndices.push_back(vertindexes[0]);
                            vtIndices.push_back(vertindexes[1]);
                            normalIndices.push_back(vertindexes[2]);
                            vertexIndices.push_back(vertindexes[(i - 1) * 3 + 0]);
                            vtIndices.push_back(vertindexes[(i - 1) * 3 + 1]);
                            normalIndices.push_back(vertindexes[(i - 1) * 3 + 2]);
                            vertexIndices.push_back(vertindexes[i * 3 + 0]);
                            vtIndices.push_back(vertindexes[i * 3 + 1]);
                            normalIndices.push_back(vertindexes[i * 3 + 2]);
                        }
                    }
                    //Чтобы не потерялся считанный токен, ставится флаг о том что он сохранён
                    cont = true;
                }
            }
        }
    }

    // Теперь обработка массивов индексов и создание выходных массивов
    // Для каждой вершины в массиве значения, соответсвующие вершине
    // под указанным индексом заносятся в выходной массив
    size_t tmpsize = vertexIndices.size();
    for (unsigned int i = 0; i < tmpsize; i++)
    {
        //Надо учесть что индексы в файле начинаются с 1!
        vec3 vertex = temp_vertices[vertexIndices[i] - 1];
        outVertices.push_back(vertex);
        vec3 normal = temp_normals[normalIndices[i] - 1];
        outNormals.push_back(normal);
        vec2 vt = temp_textures[vtIndices[i] - 1];
        outTextures.push_back(vt);
    }
    return true;
}
