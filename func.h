#pragma once

#include "globals.h"

/// </summary>
/// �������� ������� �� �����
/// </summary>
/// <param name="filename">- ���� � �����.</param>
/// <returns>- ������ � ����� �������.</returns>
string LoadShader(const char* filename);

/// </summary>
/// ������� ������������� �������� � �������� ����.
/// /// </summary>
/// <returns>��������� �� ��������� ����.</returns>
GLFWwindow* InitMain();

/// </summary>
/// ���������� ������� ������.
/// /// </summary>
/// <param name="window">- ��������� �� ����.</param>
/// <param name="key">- ��� �������.</param>
/// <param name="scancode">- ��� �������.</param>
/// <param name="action">- ��������.</param>
/// <param name="mods">- ��������� ������������� �������.</param>
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

/// <summary>
/// ��������� ��������� ������
/// </summary>
/// <param name="window">- ��������� �� ����</param>
/// <param name="ViewMatrix">- ������� ����</param>
void getViewMatrix(GLFWwindow* window, mat4* ViewMatrix);

/// </summary>
/// �������� OBJ �����
/// </summary>
/// <param name="path">- ���� � �����.</param>
/// <param name="outVertices">- �������� ������ ��������� ������.</param>
/// <param name="outTextures">- �������� ������ ���������� ���������.</param>
/// <param name="outNormals">- �������� ������ ��������.</param>
/// <returns>������� �� �������� </returns>
bool loadOBJ(
    const char* path,
    vector<vec3>& outVertices,
    vector<vec2>& outTextures,
    vector<vec3>& outNormals
);
