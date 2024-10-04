#include "world_generation.h"

world_data::game generate_world(int seed, uint8_t difficulty, uint8_t shops, uint8_t size) {
	std::default_random_engine gen(seed);
	srand(seed);

	std::normal_distribution<float> dif_rng((float)difficulty / 2.0f, (float)difficulty / 4.0f);
	std::normal_distribution<float> sup_rng(16.0f - std::sqrt(difficulty), 3.0f - std::log10(difficulty));

	world_data::game world;
	world.systems = std::vector<world_data::system_data>(size * size);
	world.size = size;

	// generate difficulty and supplies
	for (size_t i = 0; i < size * size; i++) {
		uint8_t dif = std::max(std::min((int)std::abs(dif_rng(gen)), 255), 0);
		uint8_t sup = std::max(std::min((int)std::abs(sup_rng(gen)), 255), 0);

		world.systems[i] = world_data::system_data(sup, dif);
	}

	// generate shops
	for (size_t i = 0; i < shops; i++) {
		uint8_t x = rand() % size;
		uint8_t y = rand() % size;

		if (!world.systems[y * size + x].shop) {
			world.systems[y * size + x].shop = true;
		} else {
			i--;
		}
	}

	std::vector<std::vector<uint8_t>> fac_pos(3);

	// generate 3 starting nodes for the different factions
	for (size_t i = 0; i < 3; i++) {
		fac_pos[i].push_back((i * size / 3) + rand() % (size / 3));
		fac_pos[i].push_back(rand() % size);

		world.systems[fac_pos[i][1] * size + fac_pos[i][0]].faction = (world_data::faction_type)(i + 1);
	}

	// propogate out the factions
	const int n_nodes = 5;
	const int n_factions = 3;

	bool can_expand[3] = { 1, 1, 1 };

	while (can_expand[0] || can_expand[1] || can_expand[2]) {
		for (size_t i = 0; i < n_factions; i++) {
			if (can_expand[i]) {

				std::vector<uint8_t> valid_exp;

				// add all valid exp points to list
				for (size_t j = 0; j < fac_pos[i].size() / 2; j++) {

					int x = fac_pos[i][j * 2];
					int y = fac_pos[i][j * 2 + 1];

					if (world_data::is_valid(world, x + 1, y) && world.systems[y * world.size + x + 1].faction == world_data::faction_type::none) { valid_exp.push_back(x + 1); valid_exp.push_back(y); }
					if (world_data::is_valid(world, x - 1, y) && world.systems[y * world.size + x - 1].faction == world_data::faction_type::none) { valid_exp.push_back(x - 1); valid_exp.push_back(y); }
					if (world_data::is_valid(world, x, y + 1) && world.systems[(y + 1) * world.size + x].faction == world_data::faction_type::none) { valid_exp.push_back(x); valid_exp.push_back(y + 1); }
					if (world_data::is_valid(world, x, y - 1) && world.systems[(y - 1) * world.size + x].faction == world_data::faction_type::none) { valid_exp.push_back(x); valid_exp.push_back(y - 1); }
				}

				if (valid_exp.size() == 0) {
					can_expand[i] = false;
				}

				// after adding all valid expansion points, expand to rand n_nodes
				if (valid_exp.size() > n_nodes * 2) {

					std::unordered_set<int> indexes;
					while (indexes.size() < n_nodes) {
						indexes.insert(rand() % valid_exp.size() / 2);
					}

					for (auto it = indexes.begin(); it != indexes.end(); it++) {
						int j = *it;

						int x = valid_exp[j * 2];
						int y = valid_exp[j * 2 + 1];

						world.systems[y * size + x].faction = (world_data::faction_type)(i + 1);
						fac_pos[i].push_back(x); fac_pos[i].push_back(y);
					}
				} else {
					for (size_t j = 0; j < valid_exp.size() / 2; j++) {
						int x = valid_exp[j * 2];
						int y = valid_exp[j * 2 + 1];

						world.systems[y * size + x].faction = (world_data::faction_type)(i + 1);
						fac_pos[i].push_back(x); fac_pos[i].push_back(y);
					}
				}
			}
		}
	}

	return world;
}