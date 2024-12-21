#include <iostream>
#include <complex>
#include <chrono>

#include "../OpenglProjects/OpenglProjects.h"
#include "GLFW/glfw3.h"

struct vec2 {
	float x;
	float y;
};


struct particle {
	vec2 pos;
};


void initialize_particles(particle* particles, size_t count) {
	particles = (particle*)malloc(count * sizeof(particle));

	size_t cols = std::sqrt(count);
	size_t rows = std::ceil(std::sqrt(count));


}

void render_particles(particle* particles, size_t count) {
	for (size_t i = 0; i < count; i++) {
		draw_circle(particles[i].pos.x, particles[i].pos.y, 0.01f);
	}
}

int main()
{
	size_t width = 500;
	size_t height = 500;

	GLFWwindow* window = create_window(width, height, "Fluid Simulation");

	size_t count = 0;

	while (!glfwWindowShouldClose(window))
	{
		std::string out = "";
		count++;

		glClear(GL_COLOR_BUFFER_BIT);

		// renders stuff


		glfwSwapBuffers(window);
		glfwPollEvents();

		out.append("\u001b[HFrame: ").append(std::to_string(count)).append("\n");

		std::cout << out;
	}

	glfwTerminate();
}
