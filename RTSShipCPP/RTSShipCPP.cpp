#include <iostream>
#include <chrono>
#include <string>
#include <random>
#include <Windows.h>

#include "../OpenglProjects/OpenglProjects.h"
#include "GLFW/glfw3.h"

#include "Ship.h"

void render_ships(const std::vector<Ship>& ships, size_t xMod, size_t yMod) {
	for (size_t i = 0; i < ships.size(); i++) {
		draw_circle(ships[i].m_pos.x / xMod, ships[i].m_pos.y / yMod, 0.005f);
	}
}
void update_ships(std::vector<Ship>& pShips, const std::vector<Ship>& eShips, float deltaTime) {
	for (size_t i = 0; i < pShips.size(); i++) {
		pShips[i].update(eShips, deltaTime);
	}
}

void set_ship_pos(std::vector<Ship>& pShips, std::vector<Ship>& eShips, size_t xMod, size_t yMod) {

	std::random_device rd;

	float minX = -0.95f;
	float maxX = -0.5f;
	float minY = 0.5f;
	float maxY = 0.95f;

	std::uniform_real_distribution<float> xGen(minX, maxX);
	std::uniform_real_distribution<float> yGen(minY, maxY);

	for (size_t i = 0; i < pShips.size(); i++) {
		pShips[i].m_pos = { xGen(rd) * xMod, yGen(rd) * yMod };
	}

	minX = 0.5f;
	maxX = 0.95f;
	minY = -0.95f;
	maxY = -0.5f;

	xGen = std::uniform_real_distribution<float>(minX, maxX);
	yGen = std::uniform_real_distribution<float>(minY, maxY);

	for (size_t i = 0; i < eShips.size(); i++) {
		eShips[i].m_pos = { xGen(rd) * xMod, yGen(rd) * yMod };
	}
}

int main()
{
	const size_t width = 500;
	const size_t height = 500;

	const size_t s_count = 1;

	weapon a = weapon(0.2f, 0.1f);

	std::vector<Ship> player_ships;
	std::vector<Ship> enemy_ships;

	std::vector<projectile> player_projectiles;
	std::vector<projectile> enemy_projectiles;

	gameData gd;

	for (int i = 0; i < s_count; i++) {
		player_ships.push_back(gd.createShip(0, true));
		player_ships[i].m_acc = 0.25f * 500;
	}

	for (int i = 0; i < s_count; i++) {
		enemy_ships.push_back(gd.createShip(0, true));
		enemy_ships[i].m_acc = 0.25f * 500;
	}

	set_ship_pos(player_ships, enemy_ships, width, height);


	GLFWwindow* window = create_window(width, height, "Ship RTS Cpp");

	double frame_sum = 0.0;
	size_t count = 0;

	float deltaTime = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		auto frame_start = std::chrono::high_resolution_clock::now();

		std::string out = "";
		count++;


		glClear(GL_COLOR_BUFFER_BIT);

		update_ships(player_ships, enemy_ships, deltaTime);
		update_ships(enemy_ships, player_ships, deltaTime);

		render_ships(player_ships, width, height);
		render_ships(enemy_ships, width, height);

		glfwSwapBuffers(window);
		glfwPollEvents();

		// artificial lag
		//Sleep(100);

		auto frame_time = std::chrono::high_resolution_clock::now() - frame_start;
		frame_sum += frame_time.count() / 1000000.00;
		deltaTime = frame_time.count() / 1000000000.00;

		out.append("\u001b[HFrame: ").append(std::to_string(count)).append("\n\Game Update:\nAverage: ").append(std::to_string(frame_sum / count)).append(" (ms)   \nLast: ").
			append(std::to_string(frame_time.count() / 1000000.00)).append(" (ms)   \n\nAverage: ").append(std::to_string(1000.00 / (frame_sum / count))).append(" fps   \n");

		std::cout << out;
	}

	glfwTerminate();
}
