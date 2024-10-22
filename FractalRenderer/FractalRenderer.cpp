#include <iostream>
#include <complex>
#include <chrono>

#include "../OpenglProjects/OpenglProjects.h"
#include "GLFW/glfw3.h"

double zoom = 1.0f;
double x_offset = 0.0f;
double y_offset = 0.0f;

void render_mandlebrot(size_t width, size_t height);
double in_mandlebrot(double x, double y, size_t max_it);


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	const double zoomSpeed = 0.1;

	if (yoffset > 0) {
		zoom += zoomSpeed * zoom;
	}
	else if (yoffset < 0) {
		zoom -= zoomSpeed * zoom;
	}

	zoom = std::max(zoom, 0.01);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	const double offset_speed = 0.05;

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		y_offset += offset_speed;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		x_offset -= offset_speed;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		y_offset -= offset_speed;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		x_offset += offset_speed;
	}
}

int main()
{
	size_t width = 600;
	size_t height = 600;


	GLFWwindow* window = create_window(width, height, "Fractal Renderer");

	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	double sim_sum = 0.0;
	size_t count = 0;

	while (!glfwWindowShouldClose(window))
	{
		std::string out = "";
		count++;

		glClear(GL_COLOR_BUFFER_BIT);

		// renders entire world
		auto sim_start = std::chrono::high_resolution_clock::now();
		render_mandlebrot(width, height);
		auto sim_time = std::chrono::high_resolution_clock::now() - sim_start;
		sim_sum += sim_time.count() / 1000000.00;

		glfwSwapBuffers(window);
		glfwPollEvents();

		out.append("\u001b[HFrame: ").append(std::to_string(count)).append("\n\nSim Update:\nAverage: ").append(std::to_string(sim_sum / count)).append(" (ms)   \nLast: ").
			append(std::to_string(sim_time.count() / 1000000.00)).append(" (ms)   \n");

		std::cout << out;
	}

	glfwTerminate();
}

void render_mandlebrot(size_t width, size_t height) {

	double* pixel = (double*)malloc(width * height * sizeof(double));

	double xMin = (-2.5 + x_offset) / zoom;
	double xMax = (1.0 + x_offset) / zoom;

	double yMin = (-1.1 + y_offset) / zoom;
	double yMax = (1.1 + y_offset) / zoom;

	double scaleX = (std::abs(xMin - xMax)) / (width - 1);
	double scaleY = (std::abs(yMin - yMax)) / (height - 1);

	float radius = 2.0 / (double)width;

	#pragma omp parallel for
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {

			double fx = xMin + ((double)x * scaleX);
			double fy = yMin + ((double)y * scaleY);
			
			pixel[y * width + x] = in_mandlebrot(fx, fy, 5000);
		}
	}

	glBegin(GL_POINTS);

	size_t idx = 0;
	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {

			GLdouble px = ((2.0 * (double)x) / (double)width) - 1.0;
			GLdouble py = ((2.0 * (double)y) / (double)height) - 1.0;

			glColor3d(pixel[idx], pixel[idx] > 0.99 ? 1.0 : 0.0, pixel[idx] > 0.99 ? 1.0 : 0.0);

			glVertex2f(px, py);
			idx++;
		}
	}

	glEnd();

	free(pixel);
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