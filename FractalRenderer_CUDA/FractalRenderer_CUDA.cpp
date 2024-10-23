#include <iostream>
#include <chrono>
#include <string>


#include "../OpenglProjects/OpenglProjects.h"
#include "GLFW/glfw3.h"

#include "kernals.cuh"

double zoom = 1.0f;
double x_offset = 0.0f;
double y_offset = 0.0f;

size_t mandle_iter = 750;


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	const double zoomSpeed = 0.1;

	if (yoffset > 0) { 
		double change = zoomSpeed * zoom;
		//mandle_iter += (zoom / change) * 10.0;

		x_offset += (change * x_offset) / zoom;
		y_offset += (change * y_offset) / zoom;

		zoom += change;
	}
	else if (yoffset < 0) {
		double change = zoomSpeed * zoom;

		//size_t t = (zoom / change) * 10.0;
		//mandle_iter = t > mandle_iter ? 1 : mandle_iter - t;

		x_offset -= (change * x_offset) / zoom;
		y_offset -= (change * y_offset) / zoom;

		zoom -= change;
	}

	zoom = std::max(zoom, 0.01);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	const double offset_speed = 0.05;

	if (key == GLFW_KEY_W) {
		y_offset += offset_speed;
	}
	if (key == GLFW_KEY_A) {
		x_offset -= offset_speed;
	}
	if (key == GLFW_KEY_S) {
		y_offset -= offset_speed;
	}
	if (key == GLFW_KEY_D) {
		x_offset += offset_speed;
	}
}

struct renderer {
public:
	renderer(size_t w, size_t h) {
		cudaMalloc(&d_data, w * h * sizeof(double));
		h_data = (double*)malloc(w * h * sizeof(double));

		width = w;
		height = h;
	}

	void render() {
		double xMin = (-2.5 + x_offset) / zoom;
		double xMax = (1.0 + x_offset) / zoom;

		double yMin = (-1.1 + y_offset) / zoom;
		double yMax = (1.1 + y_offset) / zoom;

		double scaleX = (std::abs(xMin - xMax)) / (width - 1);
		double scaleY = (std::abs(yMin - yMax)) / (height - 1);

		void* args[8] = { &width, &height, &mandle_iter, &xMin, &yMin, &scaleX, &scaleY, &d_data};

		cudaLaunchKernel(&mandlebrot, ceil((width * height) / 8), 8, args, 0, nullptr);
		cudaMemcpy(h_data, d_data, width * height * sizeof(double), cudaMemcpyDeviceToHost);
		cudaDeviceSynchronize();

		glBegin(GL_POINTS);

		for (size_t y = 0; y < height; y++) {
			for (size_t x = 0; x < width; x++) {

				GLdouble px = ((2.0 * (double)x) / (double)width) - 1.0;
				GLdouble py = ((2.0 * (double)y) / (double)height) - 1.0;
				
				glColor3d(h_data[y * width + x], h_data[y * width + x] > 0.99 ? 1.0 : 0.0, h_data[y * width + x] > 0.99 ? 1.0 : 0.0);

				glVertex2f(px, py);
			}
		}

		glEnd();
	}

	~renderer() {
		cudaFree(d_data);
	}

private:
	size_t width;
	size_t height;

	double* d_data;
	double* h_data;
};

int main()
{
	size_t width = 800;
	size_t height = 450;


	GLFWwindow* window = create_window(width, height, "Fractal Renderer");

	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	double sim_sum = 0.0;
	size_t count = 0;

	renderer render(width, height);

	while (!glfwWindowShouldClose(window))
	{
		std::string out = "";
		count++;

		glClear(GL_COLOR_BUFFER_BIT);

		// renders entire world
		auto sim_start = std::chrono::high_resolution_clock::now();
		render.render();
		auto sim_time = std::chrono::high_resolution_clock::now() - sim_start;
		sim_sum += sim_time.count() / 1000000.00;

		glfwSwapBuffers(window);
		glfwPollEvents();

		out.append("\u001b[HFrame: ").append(std::to_string(count)).append("\n\nSim Update:\nAverage: ").append(std::to_string(sim_sum / count)).append(" (ms)   \nLast: ").
			append(std::to_string(sim_time.count() / 1000000.00)).append(" (ms)   \n\nMandle Iterations: ").append(std::to_string(mandle_iter)).append("\n");

		std::cout << out;
	}

	glfwTerminate();
}