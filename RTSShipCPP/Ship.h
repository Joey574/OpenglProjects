#pragma once
#include <immintrin.h>
#include <iostream>
#include <string>
#include <vector>

#include "vec2.h"
#include "weapon.h"
#include "projectile.h"
#include "gameData.h"

class Ship {
public:
	vec2 m_pos;
	vec2 m_tar;

	vec2 m_vel;
	vec2 m_dir;

	float m_acc;

	int m_health;
	int m_armor;

	int m_cost;

	int type_id;
	int uuid;

	weapon* m_weapons;
	size_t m_weapons_count;

	Ship(gameData::shipTemplate tmp, size_t uuid, bool player) :
		m_pos({0, 0}), m_tar({0, 0}),
		m_vel({0, 0}), m_dir({0, 0}),
		m_acc(tmp.acc),
		m_health(tmp.health), m_armor(tmp.armor),
		m_cost(tmp.cost),
		type_id(tmp.type_id), uuid(uuid),
		m_weapons(nullptr), m_weapons_count(0)
	{}

	void update(const std::vector<Ship>& enemy_ships, float deltaTime);

private:

	float tts() const;
	float tta() const;

	void update_position(float deltaTime);
	void fire_actions(float deltaTime);
};