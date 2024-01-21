#include "func.h"

string LoadShader(const char* filename)
{
    string res;
    ifstream file(filename, ios::in);
    if (file.is_open()) {
        stringstream sstr; // ����� ��� ������
        sstr << file.rdbuf(); // ��������� ����
        res = sstr.str();   //�������� ������ �� ������
        file.close();       //��������� ����
    }
    return res;
}

void getViewMatrix(GLFWwindow* window, mat4* ViewMatrix)
{
    int windowWidth, windowHeight; // ��������� ����
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    double mouseX, mouseY; // ������� �������
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // ���� �� ��� XZ. ��� ������ ��������, ��� ������ ������ ������� "������"
    horAngleRad += mouseSpeed * (windowWidth / 2 - mouseX);
    // ���� �� ��� Y. ��� ������ ��������, ��� ������ ������ ������� "�����"
    verAngleRad += mouseSpeed * (windowHeight / 2 - mouseY);

    glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);

    // ���������� �����������, � ������ ������� ������ (� ��� ��� �������� ������-�����)
    vec3 direction(
        cos(verAngleRad) * sin(horAngleRad),
        sin(verAngleRad),
        cos(verAngleRad) * cos(horAngleRad));

    // ���������� ����, �� ������� ������� ��� ������� ������(� ��� ��� �������� �����-������)
    vec3 right = vec3(
        sin(horAngleRad - PI / 2.0f),
        0,
        cos(horAngleRad - PI / 2.0f));

    // ���������� ������������ ��� (�� ����� ��� Y)
    vec3 up = cross(right, direction);

    // ���������� �������
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) // �����
        CamPosition.y += CamSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)  // ����
        CamPosition.y -= CamSpeed;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // ������
        CamPosition += direction * CamSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // �����
        CamPosition -= direction * CamSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // �����
        CamPosition -= right * CamSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // ������
        CamPosition += right * CamSpeed;

    *ViewMatrix = lookAt(CamPosition, CamPosition + direction, up); // ������ ���� �������
}

GLFWwindow* InitMain()
{
    setlocale(LC_ALL, "Russian"); // ��� ������ � ������� ���������

    GLFWwindow* window = nullptr;
    if (!glfwInit()) {  // ������������� glfw
        cerr << "ERROR: could not start GLFW3\n";
        exit(-1);
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, "skeleton party", NULL, NULL); // ������������� ����
    if (!window) { glfwTerminate(); exit(-1); }

    glfwSetKeyCallback(window, key_callback); // ����������� ������� ����������� �������
    glfwMakeContextCurrent(window); // ������ �������� ��������� ����

    glewExperimental = GL_TRUE; // ������������� glew

    if (glewInit() != GLEW_OK) { cerr << "ERROR: could not start GLEW\n"; return nullptr; }

    return window;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case GLFW_KEY_ESCAPE: // ��������� ���� (esc)
        if (action == GLFW_PRESS)
            glfwTerminate();
        exit(1);
        break;

    case GLFW_KEY_Z: // �������� �������� (z)
        if (action == GLFW_PRESS)
            isRotateSkull = !isRotateSkull;
        break;

    case GLFW_KEY_X: // �������� �������� (x)
        if (action == GLFW_PRESS)
            isMoveSkulls = !isMoveSkulls;
        break;

    case GLFW_KEY_UP: // �������� ������� ������ (������� �����)
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            objPosition.z -= objShift;
        break;

    case GLFW_KEY_RIGHT: // �������� ������� ������ (������� ������)
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            objPosition.x += objShift;
        break;

    case GLFW_KEY_DOWN: // �������� ������� ����� (������� ����)
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            objPosition.z += objShift;
        break;

    case GLFW_KEY_LEFT: // �������� ������� ����� (������� �����)
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            objPosition.x -= objShift;
        break;

    case GLFW_KEY_MINUS: // �������� ������� ����� (-)
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            objPosition.y -= objShift;
        break;

    case GLFW_KEY_EQUAL: // �������� ������� ���� (=)
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            objPosition.y += objShift;
        break;

    case GLFW_KEY_Q: // ���������� ������� (q)
        if ((action == GLFW_PRESS || action == GLFW_REPEAT) &&
            lights.pointLights[0].diffuse.x > 0)
            lights.pointLights[0].diffuse -= vec3(0.03f);
        break;

    case GLFW_KEY_E: // ���������� ������� (e)
        if ((action == GLFW_PRESS || action == GLFW_REPEAT) &&
            lights.pointLights[0].diffuse.x < 3)
            lights.pointLights[0].diffuse += vec3(0.03f);
        break;

    }
}

bool loadOBJ(const char* path, // ���� � ����� ������
    vector<vec3>& outVertices, // �������� ������ � ���������� ������������ 
    vector<vec2>& outTextures,  // �������� ������ � ����������� ������������ 
    vector<vec3>& outNormals // �������� ������ � ������������ �������� 
)
{
    //��������� ������� ��� �������� �������� � �������� �� �����
    vector<unsigned int> vertexIndices, vtIndices, normalIndices;
    vector<vec3> temp_vertices;
    vector<vec2> temp_textures;
    vector<vec3> temp_normals;

    //������ ��� �������� ������� �� �����
    string buf;
    //�����, �������� ���������� �����
    stringstream sstr;
    //���������� ��� ���������� ������ � ����������� ������ ������ � �����
    bool cont = false;

    //���������� �����
    ifstream file(path, ios::in);
    if (file.is_open()) {
        sstr << file.rdbuf();
        file.close();
    }
    else
        return false;

    //������� �������� ��������
    outNormals.clear();
    outVertices.clear();
    outTextures.clear();

    //������� ������� ����� �� �����
    while (cont || sstr >> buf)
    {
        cont = false;

        //��������� ���������
        if (buf == "v") {
            vec3 vertex;
            sstr >> vertex.x;
            sstr >> vertex.y;
            sstr >> vertex.z;
            temp_vertices.push_back(vertex);
        }
        //��������� ���������� ���������
        else if (buf == "vt") {
            vec2 texture;
            sstr >> texture.x;
            sstr >> texture.y;
            temp_textures.push_back(texture);
        }
        //��������� ��������
        else if (buf == "vn") {
            vec3 normal;
            sstr >> normal.x;
            sstr >> normal.y;
            sstr >> normal.z;
            temp_normals.push_back(normal);
        }
        //��������� ������
        else if (buf == "f") {
            //��������� ������� ��� �������� ���������� � �����
            vector<string> vertexes;
            vector<int> vertindexes;
            while (!cont)
            {
                //����������� �����
                sstr >> buf;
                //���� ����� �������� ������ � ������� - ��� ������������ � ������
                if (buf.find('/') != string::npos)
                    vertexes.push_back(buf);
                //���� ����� - ������ ��������� ������, �� ����������� � ���������� ��������� �����
                else
                {
                    //��� ������ �� ���������� ������ ������������ ������� ������
                    for (string vert : vertexes)
                    {
                        replace(vert.begin(), vert.end(), '/', ' ');
                        stringstream tmpstream(vert);
                        int v, vt, n;
                        tmpstream >> v;
                        tmpstream >> vt;
                        tmpstream >> n;
                        //������� ��������� � ��������� ������
                        vertindexes.push_back(v);
                        vertindexes.push_back(vt);
                        vertindexes.push_back(n);
                    }
                    //������ ��� ������� ��������� �������� ��������
                    for (int i = 0; i < 3; i++)
                    {
                        vertexIndices.push_back(vertindexes[i * 3 + 0]);
                        vtIndices.push_back(vertindexes[i * 3 + 1]);
                        normalIndices.push_back(vertindexes[i * 3 + 2]);
                    }
                    //������ ������� - ���� ��� �������� �������, ���� � �� �������
                    //�� ���� ������������� �� ����� ������������� � ����� �������������
                    size_t tmpsize = vertexes.size();
                    if (tmpsize > 3)
                    {
                        //��� ������ �� ������ ����������� ��� �������, ���������� �����������
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
                    //����� �� ��������� ��������� �����, �������� ���� � ��� ��� �� �������
                    cont = true;
                }
            }
        }
    }

    // ������ ��������� �������� �������� � �������� �������� ��������
    // ��� ������ ������� � ������� ��������, �������������� �������
    // ��� ��������� �������� ��������� � �������� ������
    size_t tmpsize = vertexIndices.size();
    for (unsigned int i = 0; i < tmpsize; i++)
    {
        //���� ������ ��� ������� � ����� ���������� � 1!
        vec3 vertex = temp_vertices[vertexIndices[i] - 1];
        outVertices.push_back(vertex);
        vec3 normal = temp_normals[normalIndices[i] - 1];
        outNormals.push_back(normal);
        vec2 vt = temp_textures[vtIndices[i] - 1];
        outTextures.push_back(vt);
    }
    return true;
}
