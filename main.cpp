#include "Model.h"
#include "func.h"

// ��������� ��������� �����
LightsInfo lights;
// ������� �������� �����
DirLight dirLight{};
// �������� �������� �����
PointLight pointLight{};

GLfloat horAngleRad;
GLfloat verAngleRad;
GLfloat objShift = 0.1;
vec3 objPosition = vec3(0, 3.65, 0);
vec3 CamPosition = { 3.5, 5.5, 0 }; // ������� ������
static const vec3 CamTarget = { 0, 0, 0 }; // ���� ������
static const vec3 axisX = { 1, 0, 0 }; // ��������� ��� Ox
static const vec3 axisY = { 0, 1, 0 }; // ��������� ��� Oy
static const vec3 axisZ = { 0, 0, 1 }; // ��������� ��� Oz
static const GLfloat CamSpeed = 0.04f; // �������� ������
static const GLfloat mouseSpeed = 0.002f; // ���������������� ����
bool isRotateSkull = false;
bool isMoveSkulls = false;

int main()
{
    srand(time(nullptr));
    GLFWwindow* window = InitMain(); // �������� ���� 

    //������� ��� �������� ��������� ������
    vector<vec3> temp_vertices;
    vector<vec2> temp_textures;
    vector<vec3> temp_normals;
    vector<vec3> temp_colors;
    vector<GLuint> temp_indices;

    // ������ - ����
    loadOBJ("models/table.obj", temp_vertices, temp_textures, temp_normals);
    Model table(window, 2);
    table.load_coords(temp_vertices.data(), temp_vertices.size());
    table.load_normals(temp_normals.data(), temp_normals.size());
    table.load_texcoord(temp_textures.data(), temp_textures.size());
    table.load_shaders("texvs.glsl", "texfs.glsl");
    table.load_texture("textures/wood1.jpg");
    table.setMaterial(vec3(0.5), vec3(0.5), vec3(0), 8);

    // ������ - ����� ��������
    loadOBJ("models/human_skull.obj", temp_vertices, temp_textures, temp_normals);
    Model humanSkull(window, 2);
    humanSkull.load_coords(temp_vertices.data(), temp_vertices.size());
    humanSkull.load_normals(temp_normals.data(), temp_normals.size());
    humanSkull.load_texcoord(temp_textures.data(), temp_textures.size());
    humanSkull.load_shaders("texvs.glsl", "texfs.glsl");
    humanSkull.load_texture("textures/skull1.jpg");
    humanSkull.setMaterial(vec3(0.2), vec3(0.5), vec3(0), 32);

    // ������ - 1�� ����� ������ ����
    loadOBJ("models/Bull_skull1.obj", temp_vertices, temp_textures, temp_normals);
    Model bullSkull1(window, 2);
    bullSkull1.load_coords(temp_vertices.data(), temp_vertices.size());
    bullSkull1.load_normals(temp_normals.data(), temp_normals.size());
    bullSkull1.load_texcoord(temp_textures.data(), temp_textures.size());
    bullSkull1.load_shaders("texvs.glsl", "texfs.glsl");
    bullSkull1.load_texture("textures/skull2.jpg");
    bullSkull1.setMaterial(vec3(0.2), vec3(0.5), vec3(0), 32);

    // ������ - 2�� ����� ������ ����
    loadOBJ("models/Bull_skull2.obj", temp_vertices, temp_textures, temp_normals);
    Model bullSkull2(window, 2);
    bullSkull2.load_coords(temp_vertices.data(), temp_vertices.size());
    bullSkull2.load_normals(temp_normals.data(), temp_normals.size());
    bullSkull2.load_texcoord(temp_textures.data(), temp_textures.size());
    bullSkull2.load_shaders("texvs.glsl", "texfs.glsl");
    bullSkull2.load_texture("textures/skull2.jpg");
    bullSkull2.setMaterial(vec3(0.2), vec3(0.5), vec3(0), 32);

    // ������ - ����� ���������
    loadOBJ("models/rex.obj", temp_vertices, temp_textures, temp_normals);
    Model rex(window, 2);
    rex.load_coords(temp_vertices.data(), temp_vertices.size());
    rex.load_normals(temp_normals.data(), temp_normals.size());
    rex.load_texcoord(temp_textures.data(), temp_textures.size());
    rex.load_shaders("texvs.glsl", "texfs.glsl");
    rex.load_texture("textures/skull3.jpg");
    rex.setMaterial(vec3(0.2), vec3(0.5), vec3(0), 32);

    // ������ - �����
    loadOBJ("models/lamp.obj", temp_vertices, temp_textures, temp_normals);
    Model lamp(window, 2);
    lamp.load_coords(temp_vertices.data(), temp_vertices.size());
    lamp.load_normals(temp_normals.data(), temp_normals.size());
    lamp.load_texcoord(temp_textures.data(), temp_textures.size());
    lamp.load_shaders("texvs.glsl", "texfs.glsl");
    lamp.load_texture("textures/iron.jpg");
    lamp.setMaterial(vec3(0.2), vec3(1), vec3(1), 128);

    // ������ - ���
    loadOBJ("models/floor.obj", temp_vertices, temp_textures, temp_normals);
    Model floor(window, 2);
    floor.load_coords(temp_vertices.data(), temp_vertices.size());
    floor.load_normals(temp_normals.data(), temp_normals.size());
    floor.load_texcoord(temp_textures.data(), temp_textures.size());
    floor.load_shaders("texvs.glsl", "texfs.glsl");
    floor.load_texture("textures/grass.jpeg");
    floor.setMaterial(vec3(0.2), vec3(0.2), vec3(0), 1);

    // ��������� ��������� �����
    lights.numPLights = 1;
    lights.numSLights = 0;

    // ������� �������� �����
    dirLight.ambient = vec3(0.3f);
    dirLight.diffuse = vec3(0.15f);
    dirLight.specular = vec3(0.f);
    dirLight.direction = vec3(0, 3.2, 0);

    lights.dirLight = dirLight;

    // �������� �������� �����
    pointLight.ambient = vec3(0.5f);
    pointLight.diffuse = vec3(0.8f);
    pointLight.specular = vec3(0.);
    pointLight.position = vec3(3.5, 5.5, 0);
    pointLight.constant = 1;
    pointLight.linear = 0.07;
    pointLight.quadratic = 0.017;
    lights.pointLights.push_back(pointLight);

    // ������ �������� ������
    mat4 ModelMatr = SingleMatrix;
    mat4 ViewMatr = SingleMatrix;
    mat4 ProjMatr = SingleMatrix;

    // ������� ������������� ����� ������ ����� ��
    ProjMatr = perspective(
        radians(70.0f),           // ���� ������
        (float)WIDTH / HEIGHT,   // ����������� ������
        0.01f,                  // ������� ��������� ���������
        30.0f);                // ������� ��������� ���������

    // ������� ����
    ViewMatr = lookAt(CamPosition, CamTarget, axisY);

    // ���� ����
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    // ������� ������
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // ���������� ���� �������
    glEnable(GL_DEPTH_TEST);
    // �������� �������� ����, ���� ��� �������� ������� ������ ��������� � ������
    glDepthFunc(GL_LESS);

    float
        elapsed = 0,
        rotationHumanSkull = 0,
        moveSkulls = 0,
        a = 2.f, _cos, _sin, ssin, phi = elapsed, // ���������� ���������� ��������
        x, y; // ��� ���������������� ��������� ���������� ��������

    double
        start_time = glfwGetTime(); // ����� ������ ������

    while (!glfwWindowShouldClose(window))
    {
        elapsed = glfwGetTime() - start_time;

        if (isRotateSkull)
            phi = elapsed;
        if (isMoveSkulls)
            moveSkulls = -elapsed;

        _cos = cos(phi);
        _sin = sin(phi);
        ssin = pow(_sin, 2) + 1;
        // ��������������� ��������� ���������� ��������
        x = a * sqrt(2) * _cos / ssin;
        y = a * sqrt(2) * _cos / ssin;

        glViewport(0, 0, WIDTH, HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        getViewMatrix(window, &ViewMatr); // ������ ��������� ������

        //����
        ModelMatr = SingleMatrix;
        ModelMatr = translate(ModelMatr, vec3(0));
        ModelMatr = scale(ModelMatr, vec3(1, 1, 1));
        table.render(ModelMatr, ViewMatr, ProjMatr, lights, GL_TRIANGLES);

        // ����� ������������
        ModelMatr = SingleMatrix;
        ModelMatr = translate(ModelMatr, objPosition);
        ModelMatr = rotate(ModelMatr, radians(-90.f), axisX);
        ModelMatr = rotate(ModelMatr, y, axisY);
        ModelMatr = rotate(ModelMatr, x, axisX);
        ModelMatr = scale(ModelMatr, vec3(0.03));
        humanSkull.render(ModelMatr, ViewMatr, ProjMatr, lights, GL_TRIANGLES);

        // ����� ���������
        ModelMatr = SingleMatrix;
        ModelMatr = rotate(ModelMatr, moveSkulls, axisY);
        ModelMatr = translate(ModelMatr, vec3(1.7, 3.07, 0));
        ModelMatr = rotate(ModelMatr, radians(15.f), axisY);
        ModelMatr = rotate(ModelMatr, radians(-108.5f), axisX);
        ModelMatr = scale(ModelMatr, vec3(0.04));
        rex.render(ModelMatr, ViewMatr, ProjMatr, lights, GL_TRIANGLES);

        // �����
        ModelMatr = SingleMatrix;
        ModelMatr = translate(ModelMatr, vec3(5, 0, 0));
        ModelMatr = scale(ModelMatr, vec3(0.01));
        lamp.render(ModelMatr, ViewMatr, ProjMatr, lights, GL_TRIANGLES);

        // ���� �����
        ModelMatr = SingleMatrix;
        ModelMatr = translate(ModelMatr, vec3(2, -0.5, 0));
        ModelMatr = scale(ModelMatr, vec3(0.07));
        ModelMatr = rotate(ModelMatr, radians(-90.f), axisX);
        floor.render(ModelMatr, ViewMatr, ProjMatr, lights, GL_TRIANGLES);

        // ����� ������
        ModelMatr = SingleMatrix;
        ModelMatr = rotate(ModelMatr, moveSkulls, axisY);
        ModelMatr = translate(ModelMatr, { 0, 3.15, 1.5 });
        ModelMatr = rotate(ModelMatr, radians(-75.0f), axisY);
        ModelMatr = rotate(ModelMatr, radians(-45.0f), axisX);
        ModelMatr = scale(ModelMatr, vec3(0.07));
        bullSkull1.render(ModelMatr, ViewMatr, ProjMatr, lights, GL_TRIANGLES);
        bullSkull2.render(ModelMatr, ViewMatr, ProjMatr, lights, GL_TRIANGLES);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    return 0;

}
