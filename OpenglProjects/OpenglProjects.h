#pragma once
#include <iostream>
#include <immintrin.h>

#include <GLFW/glfw3.h>

GLFWwindow* create_window(size_t width, size_t height, const std::string& name);

void set_scroll_callback(GLFWwindow* window, GLFWscrollfun scroll_callback);
void set_key_callback(GLFWwindow* window, GLFWkeyfun key_callback);

void draw_circle(float x, float y, float r);
void draw_square(float x, float y, float r);
void set_pixel(GLfloat x, GLfloat y);