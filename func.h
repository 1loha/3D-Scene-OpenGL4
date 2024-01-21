#pragma once

#include "globals.h"

/// </summary>
/// Загрузка шейдера из файла
/// </summary>
/// <param name="filename">- путь к файлу.</param>
/// <returns>- строка с кодом шейдера.</returns>
string LoadShader(const char* filename);

/// </summary>
/// Функция инициализации главного и создания окна.
/// /// </summary>
/// <returns>Указатель на созданное окно.</returns>
GLFWwindow* InitMain();

/// </summary>
/// Обработчик нажатия клавиш.
/// /// </summary>
/// <param name="window">- указатель на окно.</param>
/// <param name="key">- код клавиши.</param>
/// <param name="scancode">- код символа.</param>
/// <param name="action">- действие.</param>
/// <param name="mods">- состояние модификаторов нажатия.</param>
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

/// <summary>
/// Изменение положения камеры
/// </summary>
/// <param name="window">- указатель на окно</param>
/// <param name="ViewMatrix">- матрица вида</param>
void getViewMatrix(GLFWwindow* window, mat4* ViewMatrix);

/// </summary>
/// Загрузка OBJ файла
/// </summary>
/// <param name="path">- путь к файлу.</param>
/// <param name="outVertices">- выходной массив координат вершин.</param>
/// <param name="outTextures">- выходной массив текстурных координат.</param>
/// <param name="outNormals">- выходной массив нормалей.</param>
/// <returns>успешна ли загрузка </returns>
bool loadOBJ(
    const char* path,
    vector<vec3>& outVertices,
    vector<vec2>& outTextures,
    vector<vec3>& outNormals
);
