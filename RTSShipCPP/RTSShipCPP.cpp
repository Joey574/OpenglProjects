#include <iostream>
#include <chrono>
#include <string>
#include <random>

#include "../OpenglProjects/OpenglProjects.h"
#include "GLFW/glfw3.h"

#include "Ship.h"

void render_ships(Ship* ships, size_t count) {
	for (size_t i = 0; i < count; i++) {
		draw_circle(ships[i].m_pos.x, ships[i].m_pos.y, 0.005f);
	}
}
void update_ships(Ship* pShips, Ship* eShips, size_t pCount, float deltaTime) {
	for (size_t i = 0; i < pCount; i++) {
		pShips[i].update(eShips, deltaTime);
	}
}

void set_ship_pos(Ship* pShips, Ship* eShips, size_t pCount, size_t eCount) {

	std::random_device rd;

	float minX = -0.95f;
	float maxX = -0.5f;
	float minY = 0.5f;
	float maxY = 0.95f;

	std::uniform_real_distribution<float> xGen(minX, maxX);
	std::uniform_real_distribution<float> yGen(minY, maxY);

	for (size_t i = 0; i < pCount; i++) {
		pShips[i].m_pos = { xGen(rd), yGen(rd) };
	}

	minX = 0.5f;
	maxX = 0.95f;
	minY = -0.95f;
	maxY = -0.5f;

	xGen = std::uniform_real_distribution<float>(minX, maxX);
	yGen = std::uniform_real_distribution<float>(minY, maxY);

	for (size_t i = 0; i < eCount; i++) {
		eShips[i].m_pos = { xGen(rd), yGen(rd) };
	}
}

int main()
{
	size_t width = 500;
	size_t height = 500;

	const size_t s_count = 100;

	Ship* player_ships = (Ship*)malloc(s_count * sizeof(Ship));
	Ship* enemy_ships = (Ship*)malloc(s_count * sizeof(Ship));

	if (player_ships == NULL || enemy_ships == NULL) {
		return 1;
	}

	for (int i = 0; i < s_count; i++) {
		player_ships[i].m_acc = 0.25f;
	}

	for (int i = 0; i < s_count; i++) {
		enemy_ships[i].m_acc = 0.25f;
	}

	set_ship_pos(player_ships, enemy_ships, s_count, s_count);


	GLFWwindow* window = create_window(width, height, "Ship RTS Cpp");

	double frame_sum = 0.0;
	size_t count = 0;

	float deltaTime = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		auto frame_start = std::chrono::high_resolution_clock::now();

		std::string out = "";
		count++;


		glClear(GL_COLOR_BUFFER_BIT);

		update_ships(player_ships, enemy_ships, s_count, deltaTime);
		update_ships(enemy_ships, player_ships, s_count, deltaTime);

		render_ships(player_ships, s_count);
		render_ships(enemy_ships, s_count);

		glfwSwapBuffers(window);
		glfwPollEvents();


		auto frame_time = std::chrono::high_resolution_clock::now() - frame_start;
		frame_sum += frame_time.count() / 1000000.00;
		deltaTime = frame_time.count() / 1000000000.00;


		out.append("\u001b[HFrame: ").append(std::to_string(count)).append("\n\Game Update:\nAverage: ").append(std::to_string(frame_sum / count)).append(" (ms)   \nLast: ").
			append(std::to_string(frame_time.count() / 1000000.00)).append(" (ms)   \n\nAverage: ").append(std::to_string(1000.00 / (frame_sum / count))).append(" fps   \n");

		std::cout << out;
	}

	free(player_ships);
	free(enemy_ships);

	glfwTerminate();
}

