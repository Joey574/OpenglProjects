#include "OpenglProjects.h"

static const float PI = 3.1415926f;

GLFWwindow* create_window(size_t width, size_t height, const std::string& name) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return nullptr;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Set up user input functions

    return window;
}

void set_scroll_callback(GLFWwindow* window, GLFWscrollfun scroll_callback) {
    glfwSetScrollCallback(window, scroll_callback);
}
void set_key_callback(GLFWwindow* window, GLFWkeyfun key_callback) {
    glfwSetKeyCallback(window, key_callback);
}

void draw_circle(float x, float y, float r) {
    const __m256 _t = _mm256_set1_ps(2.0f * PI / 23.0f);

    const __m256 _r = _mm256_set1_ps(r);
    const __m256 _x = _mm256_set1_ps(x);
    const __m256 _y = _mm256_set1_ps(y);

    // const iteration values for triangle fan
    const __m256 _a = { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f };
    const __m256 _b = { 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f };
    const __m256 _c = { 16.0f, 17.0f, 18.0f, 19.0f, 20.0f, 21.0f, 22.0f, 23.0f };

    // x values for vertexes
    __m256 _x1 = _mm256_fmadd_ps(_r, _mm256_cos_ps(_mm256_mul_ps(_t, _a)), _x);
    __m256 _x2 = _mm256_fmadd_ps(_r, _mm256_cos_ps(_mm256_mul_ps(_t, _b)), _x);
    __m256 _x3 = _mm256_fmadd_ps(_r, _mm256_cos_ps(_mm256_mul_ps(_t, _c)), _x);

    // y values for vertexes
    __m256 _y1 = _mm256_fmadd_ps(_r, _mm256_sin_ps(_mm256_mul_ps(_t, _a)), _y);
    __m256 _y2 = _mm256_fmadd_ps(_r, _mm256_sin_ps(_mm256_mul_ps(_t, _b)), _y);
    __m256 _y3 = _mm256_fmadd_ps(_r, _mm256_sin_ps(_mm256_mul_ps(_t, _c)), _y);

    float comp_x[24];
    float comp_y[24];

    _mm256_store_ps(&comp_x[0], _x1);
    _mm256_store_ps(&comp_x[8], _x2);
    _mm256_store_ps(&comp_x[16], _x3);

    _mm256_store_ps(&comp_y[0], _y1);
    _mm256_store_ps(&comp_y[8], _y2);
    _mm256_store_ps(&comp_y[16], _y3);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);

    for (int i = 0; i < 24; i++) {
        glVertex2f(comp_x[i], comp_y[i]);
    }

    glEnd();
}
void draw_square(float x, float y, float r) {
    glBegin(GL_QUADS);

    glVertex2f(x + r, y + r);
    glVertex2f(x + r, y - r);
    glVertex2f(x - r, y - r);
    glVertex2f(x - r, y + r);

    glEnd();
}
void set_pixel(GLfloat x, GLfloat y) {
    glBegin(GL_POINTS);

    glVertex2f(x, y);

    glEnd();
}