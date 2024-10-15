#pragma once
#include "pch.h"

#include "world_data.h"
#include "world_generation.h"

#include "../OpenglProjects/OpenglProjects.h"
#include "GLFW/glfw3.h"

class game {
public:

	struct player_data {
		uint8_t x_pos, y_pos, supplies;
	};

	void run();

	void render_game_world();

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	GLFWwindow* window;

	player_data player;
	world_data::game game;

	float zoom = 1.0f;
};