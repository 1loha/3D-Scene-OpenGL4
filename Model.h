#pragma once

#include "globals.h"

// Основной класс модели объекта. Содержит методы для загрузки параметров и рендеринга.
class Model
{
public:
    /// <summary>
    /// конструктор - создаёт массив вершин, пока пустой. И подключает окно.
    /// </summary>
    /// <param name="w">- указатель на окно.</param>
    /// <param name="mode">- тип модели. 0 - цветная, 1 - с материалом, 2 - с текстурой.</param>
    Model(GLFWwindow* w, GLuint mode = 0) {
        glGenVertexArrays(1, &vao);
        window = w;
        modelMode = mode;
    };

    //Деструктор.
    ~Model() {};

    /// <summary>
    /// Рендер с поддержкой освещения
    /// </summary>
    /// <param name="modelMatrix">- матрица модели.</param>
    /// <param name="viewMatrix">- матрица вида.</param>
    /// <param name="projMatrix">- матрица проекции.</param>
    /// <param name="lights">- параметры освещения сцены.</param>
    /// <param name="mode">- режим рисования.</param>
    void render(mat4 modelMatrix, mat4 viewMatrix, mat4 projMatrix, LightsInfo lights, GLuint mode);

    /// <summary>
    /// Метод для загрузки координат вершин.
    /// </summary>
    /// <param name="verteces">- массив с координатами.</param>
    /// <param name="count">- размер массива.</param>
    void load_coords(vec3* verteces, size_t count);

    /// <summary>
    /// Метод для загрузки нормалей
    /// </summary>
    /// <param name="normals">- массив с нормалями.</param>
    /// <param name="count">- размер массива.</param>
    void load_normals(vec3* normals, size_t count);

    /// <summary>
    /// Метод для загрузки текстурных координат.
    /// </summary>
    /// <param name="tex">- массив с текстурными координатами.</param>
    /// <param name="count">- размер массива.</param>
    void load_texcoord(vec2* tex, size_t count);

    /// <summary>
    /// Метод для загрузки текстур.
    /// </summary>
    /// <param name="path">- путь к основной текстуре.</param>
    void load_texture(string path);

    /// <summary>
    /// Метод для загрузки вершинного и фрагментного шейдеров.
    /// В результате выполнения будет скомпонована шейдерная программа.
    /// </summary>
    /// <param name="vect">- путь к вершинному шейдеру</param>
    /// <param name="frag">- путь к фрагментному шейдеру</param>
    void load_shaders(const char* vect, const char* frag);

    /// <summary>
    /// Метод для задания параметров материала
    /// </summary>
    /// <param name="a">- фоновый свет.</param>
    /// <param name="d">- диффузный свет.</param>
    /// <param name="s">- отражённый свет.</param>
    /// <param name="shine">- глянцевость.</param>
    void setMaterial(vec3 a, vec3 d, vec3 s, GLfloat shine);

private:

    // ID массива вершин
    GLuint vao = -1;

    // Количество вершин
    size_t verteces_count = 0;

    // Количество индексов
    size_t indices_count = 0;

    // ID шейдерной программы
    GLuint shader_programme = -1;

    // Указатель на окно
    GLFWwindow* window;

    // Материал из которого состоит объект
    Material material;

    // Вспомогательная переменная, устанавливающая тип модели - с цветами или материалом/текстурой
    GLuint modelMode = 0;

    // Текстура
    GLuint texture = -1;
};

