#pragma once

#include "globals.h"

// �������� ����� ������ �������. �������� ������ ��� �������� ���������� � ����������.
class Model
{
public:
    /// <summary>
    /// ����������� - ������ ������ ������, ���� ������. � ���������� ����.
    /// </summary>
    /// <param name="w">- ��������� �� ����.</param>
    /// <param name="mode">- ��� ������. 0 - �������, 1 - � ����������, 2 - � ���������.</param>
    Model(GLFWwindow* w, GLuint mode = 0) {
        glGenVertexArrays(1, &vao);
        window = w;
        modelMode = mode;
    };

    //����������.
    ~Model() {};

    /// <summary>
    /// ������ � ���������� ���������
    /// </summary>
    /// <param name="modelMatrix">- ������� ������.</param>
    /// <param name="viewMatrix">- ������� ����.</param>
    /// <param name="projMatrix">- ������� ��������.</param>
    /// <param name="lights">- ��������� ��������� �����.</param>
    /// <param name="mode">- ����� ���������.</param>
    void render(mat4 modelMatrix, mat4 viewMatrix, mat4 projMatrix, LightsInfo lights, GLuint mode);

    /// <summary>
    /// ����� ��� �������� ��������� ������.
    /// </summary>
    /// <param name="verteces">- ������ � ������������.</param>
    /// <param name="count">- ������ �������.</param>
    void load_coords(vec3* verteces, size_t count);

    /// <summary>
    /// ����� ��� �������� ��������
    /// </summary>
    /// <param name="normals">- ������ � ���������.</param>
    /// <param name="count">- ������ �������.</param>
    void load_normals(vec3* normals, size_t count);

    /// <summary>
    /// ����� ��� �������� ���������� ���������.
    /// </summary>
    /// <param name="tex">- ������ � ����������� ������������.</param>
    /// <param name="count">- ������ �������.</param>
    void load_texcoord(vec2* tex, size_t count);

    /// <summary>
    /// ����� ��� �������� �������.
    /// </summary>
    /// <param name="path">- ���� � �������� ��������.</param>
    void load_texture(string path);

    /// <summary>
    /// ����� ��� �������� ���������� � ������������ ��������.
    /// � ���������� ���������� ����� ������������ ��������� ���������.
    /// </summary>
    /// <param name="vect">- ���� � ���������� �������</param>
    /// <param name="frag">- ���� � ������������ �������</param>
    void load_shaders(const char* vect, const char* frag);

    /// <summary>
    /// ����� ��� ������� ���������� ���������
    /// </summary>
    /// <param name="a">- ������� ����.</param>
    /// <param name="d">- ��������� ����.</param>
    /// <param name="s">- ��������� ����.</param>
    /// <param name="shine">- �����������.</param>
    void setMaterial(vec3 a, vec3 d, vec3 s, GLfloat shine);

private:

    // ID ������� ������
    GLuint vao = -1;

    // ���������� ������
    size_t verteces_count = 0;

    // ���������� ��������
    size_t indices_count = 0;

    // ID ��������� ���������
    GLuint shader_programme = -1;

    // ��������� �� ����
    GLFWwindow* window;

    // �������� �� �������� ������� ������
    Material material;

    // ��������������� ����������, ��������������� ��� ������ - � ������� ��� ����������/���������
    GLuint modelMode = 0;

    // ��������
    GLuint texture = -1;
};

