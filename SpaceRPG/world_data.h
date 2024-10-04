#pragma once

#include "pch.h"

static class world_data {
public:

	enum class faction_type {
		none=0, void_reavers=1, solis_vangaurd=2, nebulons=3
	};

	struct system_data {

		system_data() : supplies(0), danger(0), faction(faction_type::none), shop(false), discovered(false) {}
		system_data(uint8_t supplies, uint8_t danger) : supplies(supplies), danger(danger), faction(faction_type::none), shop(false), discovered(false) {}

		uint8_t supplies;
		uint8_t danger;
		faction_type faction;
		bool shop;
		bool discovered;
	};

	struct game {
		uint8_t size;
		std::vector<world_data::system_data> systems;
	};

	static inline bool is_valid(const world_data::game& game, int  x, int y) {
		return x >= 0 && y >= 0 && x < game.size && y < game.size;
	}

	static void update_discovered(world_data::game& game, int x, int y) {
		if (is_valid(game, x, y)) { game.systems[y * game.size + x].discovered = true; }

		if (is_valid(game, x + 1, y)) { game.systems[y * game.size + x + 1].discovered = true; }
		if (is_valid(game, x - 1, y)) { game.systems[y * game.size + x - 1].discovered = true; }
		if (is_valid(game, x, y + 1)) { game.systems[(y + 1) * game.size + x].discovered = true; }
		if (is_valid(game, x, y - 1)) { game.systems[(y - 1) * game.size + x].discovered = true; }
	}
};

