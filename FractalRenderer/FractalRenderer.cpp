#include <iostream>
#include <complex>

#include "../OpenglProjects/OpenglProjects.h"
#include "GLFW/glfw3.h"

double zoom = 1.0f;
double x_offset = 0.0f;
double y_offset = 0.0f;

void render_mandlebrot(size_t width, size_t height);
double in_mandlebrot(double x, double y, size_t max_it);


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	const float zoomSpeed = 0.1f;

	if (yoffset > 0) {
		zoom += zoomSpeed * zoom;
	}
	else if (yoffset < 0) {
		zoom -= zoomSpeed * zoom;
	}

	zoom = std::max(zoom, 0.01);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	const float offset_speed = 0.05f;

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {

	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {

	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {

	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {

	}
}

int main()
{
	size_t width = 600;
	size_t height = 600;


	GLFWwindow* window = create_window(width, height, "Fractal Renderer");

	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// renders entire world
		render_mandlebrot(width, height);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void render_mandlebrot(size_t width, size_t height) {

	double xMin = -2.5f / zoom;
	double xMax = 1.0f / zoom;

	double yMin = -1.1f / zoom;
	double yMax = 1.1f / zoom;

	double scaleX = (std::abs(xMin - xMax)) / (width - 1);
	double scaleY = (std::abs(yMin - yMax)) / (height - 1);

	float radius = 1.0 / (double)width;

	for (double y = 0; y < height; y++) {
		for (double x = 0; x < width; x++) {
			double fx = ((x * radius) / (double)width) - 1.0f;
			double fy = ((y * radius) / (double)width) - 1.0f;

			std::cout << fx << ", " << fy << "\n";

			draw_square(fx, fy, radius);
		}
	}


}
double in_mandlebrot(double x, double y, size_t max_it) {
    std::complex<double> c(x, y);
    std::complex<double> z = 0;

    for (size_t i = 0; i < max_it; ++i) {
        z = z * z + c;
        if (std::abs(z) > 2) {
            return 1.00 - (1.00 / (((double)i / 50.00) + 1.00)); // Point is outside + smooth
        }
    }
    return 1.00; // Point is inside the Mandelbrot set
}