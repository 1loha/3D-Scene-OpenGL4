#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

constexpr auto PI = 3.14159265358979323846f;

// ������ ������
constexpr auto WIDTH = 1200;

// ������ ������
constexpr auto HEIGHT = 1000;

using namespace std;
using namespace glm;

// ��������� � ������� ��� �������� �������. �������� ����������� �� ��������� � ����������� "�������"
struct Material
{
    vec3 ka; // ����. �������� ��������� (���� �������� ���������)
    vec3 kd; // ����. ���������� ��������� (���� �������)
    vec3 ks; // ����. ����������� �����
    GLfloat shininess; // ���������� �����������

    // �������� �� ���������
    Material()
    {
        ka = vec3(0.0215, 0.1745, 0.0215);
        kd = vec3(0.07568, 0.61424, 0.07568);
        ks = vec3(0.633, 0.727811, 0.633);
        shininess = 128 * 0.6;
    };
};

// ��������� � ��������� ���������� �������� ���������
struct DirLight
{
    // �����������
    vec3 direction;

    // ��������� �����
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
extern DirLight dirLight;

// ��������� � ��������� ��������� ��������� �����
struct PointLight
{
    // ����������
    vec3 position;

    // ���������
    float constant;
    float linear;
    float quadratic;

    // ��������� �����
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
extern PointLight pointLight;

// ��������� � ��������� ������������� ��������� �����
struct SpotLight
{
    //�������������� � �����������
    vec3 position;
    vec3 direction;

    //������ ����
    float cutOff;
    float outerCutOff;

    // ���������
    float constant;
    float linear;
    float quadratic;

    // ��������� �����
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
extern SpotLight spotLight;

// ��������� � ��������� ���������� ����� �� �����
struct LightsInfo
{
    /// ��������� �������� ���������
    DirLight dirLight;

    // ������ � ��������� ����������� �����
    vector<PointLight> pointLights;

    // ������ � ������������� ����������� �����
    vector<SpotLight> spotLights;

    //���������� �������� � ������������ ���������� �����
    int numPLights;
    int numSLights;
};
extern LightsInfo lights;

// ��������� ������� ��� ������ ��������
const mat4 SingleMatrix = mat4(1.0f);

// ������� ������
extern vec3 CamPosition;

// ������� ������������ �������
extern vec3 objPosition;

// �������� ������ �������
extern GLfloat objShift;

// ���������� �� �������� �������� ������������� ������
extern bool isRotateSkull;

// ���������� �� �������� ��������� ��������
extern bool isMoveSkulls;

// ���������� �� �������� �������� ������������� ������
extern bool isMoveSkull;

// �������������� ���� ��� �������� ������ �����
extern GLfloat horAngleRad;

// ������������ ���� ��� �������� ������ �����
extern GLfloat verAngleRad;

// �������� ������
extern const GLfloat CamSpeed;

// ���������������� ����
extern const GLfloat mouseSpeed;