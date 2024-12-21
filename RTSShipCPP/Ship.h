#pragma once
#include <immintrin.h>

#include "vec2.h"
#include "weapon.h"
#include "projectile.h"

class Ship {
public:
	vec2 m_pos;
	vec2 m_vel;
	vec2 m_dir;

	float m_acc;

	vec2 m_target;

	weapon* m_weapons;
	size_t m_weapons_count;

	Ship(weapon* weapons, size_t weapon_count) : m_pos({ 0.0f, 0.0f }), m_vel({ 0.0f, 0.0f }), m_dir({ 0.0f, 0.0f }), m_target({0.0f, 0.0f}), m_acc(0.0f), m_weapons(weapons), m_weapons_count(weapon_count) {}

	void update(Ship* enemy_ships, float deltaTime);

private:

	float tts(float deltaTime) const;
	float tta(float deltaTime) const;

	void update_position(float deltaTime);
	void fire_actions(float deltaTime);
};