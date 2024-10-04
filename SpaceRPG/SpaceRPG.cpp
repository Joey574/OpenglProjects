#include "pch.h"

#include "../OpenglProjects/OpenglProjects.h"
#include "GLFW/glfw3.h"

#include "world_generation.h"
#include "player_data.h"
#include "world_data.h"


float zoom = 1.0f;
player_data player;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	const float zoomSpeed = 0.1f;

	if (yoffset > 0) {
		zoom += zoomSpeed * zoom;
	}
	else if (yoffset < 0) {
		zoom -= zoomSpeed * zoom;
	}

	zoom = std::max(zoom, 0.1f);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	const float offset_speed = 0.05f;

	if ( key == GLFW_KEY_W && action == GLFW_PRESS) {
		player.y_pos++;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		player.x_pos--;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		player.y_pos--;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		player.x_pos++;
	}
}


void render_game_world(world_data::game game) {

	const float world_size = 0.35f;
	float radius = world_size / game.size;


	for (uint8_t r = 0; r < game.size; r++) {
		for (uint8_t c = 0; c < game.size; c++) {

			// scale to [-1, 1]
			float f_c = ((float)c / ((game.size) / 2.0f) - 1.0f) * zoom;
			float f_r = ((float)r / ((game.size) / 2.0f) - 1.0f) * zoom;

			// set color based on player, discovered, shop, then faction type
		 	player.x_pos == c && player.y_pos == r ? glColor3f(1.0f, 1.0f, 1.0f):
				!game.systems[r * game.size + c].discovered ? glColor3f(0.2f, 0.2f, 0.2f) :
				game.systems[r * game.size + c].shop ? glColor3f(1.0f, 0.0f, 1.0f) :
				game.systems[r * game.size + c].faction == world_data::faction_type::solis_vangaurd ? glColor3f(0.75f, 0.0f, 0.0f) :
				game.systems[r * game.size + c].faction == world_data::faction_type::void_reavers ? glColor3f(0.0f, 0.75f, 0.0f) :
				game.systems[r * game.size + c].faction == world_data::faction_type::nebulons ? glColor3f(0.0f, 0.0f, 0.75f) :
				glColor3f(1.0f, 1.0f, 1.0f); // <- should never be set to this
				
			draw_square(f_c, f_r, radius * zoom);
		}
	}
}

int main()
{
	GLFWwindow* window = create_window(780, 780);

	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	world_data::game game = generate_world(45632, 10, 10, 20);

	// set player position
	player.x_pos = 0;
	player.y_pos = 0;
	

	/*for (int i = 0; i < game.systems.size(); i++) {
		game.systems[i].discovered = true;
	}*/

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// renders entire world
		world_data::update_discovered(game, player.x_pos, player.y_pos);
		render_game_world(game);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}