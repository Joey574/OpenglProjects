#pragma once
#include <array>

#include "Ship.h"

struct gameData {
public:

	const enum class shipType {
		corvette,
		frigate,
		destroyer,
		cruiser,
		battleship
	};

	struct shipTemplate {
		std::string name;
		int type_id;

		int health;
		int armor;
		float acc;

		int cost;

		int s_wm;
		int m_wm;
		int l_wm;

		float radius;
		shipType type;

		shipTemplate(std::string name, int tid, int hp, int ap, float acc, int cost, int swm, int mwm, int lwm, float r, shipType type) :
			name(name), type_id(tid), 
			health(hp), armor(ap), acc(acc),
			cost(cost), 
			s_wm(swm), m_wm(mwm), l_wm(lwm),
			radius(r), type(type)
		{}
	};
	struct weaponTemplate {
		std::string name;
		int type_id;

		float range;
		float inaccuracy;
		float speed;
		float cooldown;

		int damage;
		int ap;

		weaponTemplate(std::string name, int tid, float range, float inac, float sped, float cool, int dam, int ap) :
			name(name), type_id(tid), 
			range(range), inaccuracy(inac), speed(sped), cooldown(cool), 
			damage(dam), ap(ap)
		{}
	};

	const std::array<shipTemplate, 36> ships = {
		shipTemplate("starship_07",  0, cor_hp, cor_ap, cor_ac, cor_co, 2,0,0, 0.15f, shipType::corvette),
		shipTemplate("starship_13",  1, cor_hp, cor_ap, cor_ac, cor_co, 2,0,0, 0.20f, shipType::corvette),

		shipTemplate("starship_14",  2, fri_hp, fri_ap, fri_ac, fri_co, 2,1,0, 0.30f, shipType::frigate),
		shipTemplate("starship_15",  3, fri_hp, fri_ap, fri_ac, fri_co, 2,1,0, 0.25f, shipType::frigate),
		shipTemplate("starship_18",  4, fri_hp, fri_ap, fri_ac, fri_co, 2,1,0, 0.25f, shipType::frigate),
		shipTemplate("starship_22",  5, fri_hp, fri_ap, fri_ac, fri_co, 2,1,0, 0.25f, shipType::frigate),
		shipTemplate("starship_23",  6, fri_hp, fri_ap, fri_ac, fri_co, 2,1,0, 0.20f, shipType::frigate),
		shipTemplate("starship_24",  7, fri_hp, fri_ap, fri_ac, fri_co, 2,1,0, 0.25f, shipType::frigate),
		shipTemplate("starship_26",  8, fri_hp, fri_ap, fri_ac, fri_co, 2,1,0, 0.25f, shipType::frigate),
		shipTemplate("starship_27",  9, fri_hp, fri_ap, fri_ac, fri_co, 2,1,0, 0.20f, shipType::frigate),
		shipTemplate("starship_28", 10, fri_hp, fri_ap, fri_ac, fri_co, 2,1,0, 0.25f, shipType::frigate),
		shipTemplate("starship_30", 11, fri_hp, fri_ap, fri_ac, fri_co, 2,1,0, 0.30f, shipType::frigate),

		shipTemplate("starship_01", 12, des_hp, des_ap, des_ac, des_co, 1,3,1, 0.25f, shipType::destroyer),
		shipTemplate("starship_02", 13, des_hp, des_ap, des_ac, des_co, 1,3,1, 0.30f, shipType::destroyer),
		shipTemplate("starship_03", 14, des_hp, des_ap, des_ac, des_co, 1,3,1, 0.30f, shipType::destroyer),
		shipTemplate("starship_04", 15, des_hp, des_ap, des_ac, des_co, 1,3,1, 0.25f, shipType::destroyer),
		shipTemplate("starship_05", 16, des_hp, des_ap, des_ac, des_co, 1,3,1, 0.30f, shipType::destroyer),
		shipTemplate("starship_06", 17, des_hp, des_ap, des_ac, des_co, 1,3,1, 0.30f, shipType::destroyer),
		shipTemplate("starship_08", 18, des_hp, des_ap, des_ac, des_co, 1,3,1, 0.35f, shipType::destroyer),
		shipTemplate("starship_11", 19, des_hp, des_ap, des_ac, des_co, 1,3,1, 0.30f, shipType::destroyer),
		shipTemplate("starship_12", 20, des_hp, des_ap, des_ac, des_co, 1,3,1, 0.30f, shipType::destroyer),
		shipTemplate("starship_16", 21, des_hp, des_ap, des_ac, des_co, 1,3,1, 0.35f, shipType::destroyer),
		shipTemplate("starship_17", 22, des_hp, des_ap, des_ac, des_co, 1,3,1, 0.30f, shipType::destroyer),
		shipTemplate("starship_20", 23, des_hp, des_ap, des_ac, des_co, 1,3,1, 0.30f, shipType::destroyer),
		shipTemplate("starship_31", 24, des_hp, des_ap, des_ac, des_co, 1,3,1, 0.30f, shipType::destroyer),
		shipTemplate("starship_32", 25, des_hp, des_ap, des_ac, des_co, 1,3,1, 0.35f, shipType::destroyer),

		shipTemplate("starship_09", 26, cru_hp, cru_ap, cru_ac, cru_co, 3,2,1, 0.40f, shipType::cruiser),
		shipTemplate("starship_10", 27, cru_hp, cru_ap, cru_ac, cru_co, 3,2,1, 0.40f, shipType::cruiser),
		shipTemplate("starship_19", 28, cru_hp, cru_ap, cru_ac, cru_co, 3,2,1, 0.40f, shipType::cruiser),
		shipTemplate("starship_21", 29, cru_hp, cru_ap, cru_ac, cru_co, 3,2,1, 0.35f, shipType::cruiser),
		shipTemplate("starship_25", 30, cru_hp, cru_ap, cru_ac, cru_co, 3,2,1, 0.35f, shipType::cruiser),
		shipTemplate("starship_29", 31, cru_hp, cru_ap, cru_ac, cru_co, 3,2,1, 0.40f, shipType::cruiser),
		shipTemplate("starship_33", 32, cru_hp, cru_ap, cru_ac, cru_co, 3,2,1, 0.40f, shipType::cruiser),

		shipTemplate("starship_34", 33, bat_hp, bat_ap, bat_ac, bat_co, 6,4,2, 0.60f, shipType::battleship),
		shipTemplate("starship_35", 34, bat_hp, bat_ap, bat_ac, bat_co, 6,4,2, 0.60f, shipType::battleship),
		shipTemplate("starship_36", 35, bat_hp, bat_ap, bat_ac, bat_co, 6,4,2, 0.80f, shipType::battleship)
	};

	//const std::array<weaponTemplate, 0> weapons = {};

	inline Ship createShip(int type, bool player) {
		return Ship(ships[type], uuid++, player);
	}

private:

	size_t uuid = 0;

	// hit points
	const int cor_hp = 10;
	const int fri_hp = 20;
	const int des_hp = 40;
	const int cru_hp = 70;
	const int bat_hp = 100;

	// armor points
	const int cor_ap = 1;
	const int fri_ap = 4;
	const int des_ap = 5;
	const int cru_ap = 8;
	const int bat_ap = 10;

	// acceleration
	const float cor_ac = 4.0f;
	const float fri_ac = 1.5f;
	const float des_ac = 1.2f;
	const float cru_ac = 0.8f;
	const float bat_ac = 0.5f;

	// cost
	const int cor_co = 100;
	const int fri_co = 250;
	const int des_co = 600;
	const int cru_co = 800;
	const int bat_co = 1000;

};