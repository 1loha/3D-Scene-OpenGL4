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

// ширина экрана
constexpr auto WIDTH = 1200;

// высота экрана
constexpr auto HEIGHT = 1000;

using namespace std;
using namespace glm;

// Структура с данными про материал объекта. Содержит конструктор по умолчанию с настройками "изумруд"
struct Material
{
    vec3 ka; // коэф. фонового отражения (цвет фонового освещения)
    vec3 kd; // коэф. диффузного отражения (цвет объекта)
    vec3 ks; // коэф. зеркального блика
    GLfloat shininess; // показатель глянцевости

    // Значения по умолчанию
    Material()
    {
        ka = vec3(0.0215, 0.1745, 0.0215);
        kd = vec3(0.07568, 0.61424, 0.07568);
        ks = vec3(0.633, 0.727811, 0.633);
        shininess = 128 * 0.6;
    };
};

// Структура с описанием параметров фонового освещения
struct DirLight
{
    // Направление
    vec3 direction;

    // Параметры света
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
extern DirLight dirLight;

// Структура с описанием точечного источника света
struct PointLight
{
    // Координаты
    vec3 position;

    // Затухание
    float constant;
    float linear;
    float quadratic;

    // Параметры света
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
extern PointLight pointLight;

// Структура с описанием направленного источника света
struct SpotLight
{
    //Местоположение и направление
    vec3 position;
    vec3 direction;

    //Радиус луча
    float cutOff;
    float outerCutOff;

    // Затухание
    float constant;
    float linear;
    float quadratic;

    // Параметры света
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
extern SpotLight spotLight;

// Структура с описанием источников света на сцене
struct LightsInfo
{
    /// Параметры фонового освещения
    DirLight dirLight;

    // Массив с точечными источниками света
    vector<PointLight> pointLights;

    // Массив с направленными источниками света
    vector<SpotLight> spotLights;

    //Количество точечных и направленных источников света
    int numPLights;
    int numSLights;
};
extern LightsInfo lights;

// единичная матрица для сброса значений
const mat4 SingleMatrix = mat4(1.0f);

// Позиция камеры
extern vec3 CamPosition;

// Позиция управляемого объекта
extern vec3 objPosition;

// величина сдвига объекта
extern GLfloat objShift;

// разрешение на анимацию поворота человеческого черепа
extern bool isRotateSkull;

// разрешение на анимацию остальных объектов
extern bool isMoveSkulls;

// разрешение на анимацию движения человеческого черепа
extern bool isMoveSkull;

// горизонтальный угол для движения камеры мышью
extern GLfloat horAngleRad;

// вертикальный угол для движения камеры мышью
extern GLfloat verAngleRad;

// скорость камеры
extern const GLfloat CamSpeed;

// чувствительность мыши
extern const GLfloat mouseSpeed;