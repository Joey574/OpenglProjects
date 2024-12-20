#pragma once
#include "vec2.h"
#include "Weapon.h"

class Ship {
public:
	vec2 m_pos;
	vec2 m_vel;
	vec2 m_dir;

	float m_acc;

	vec2 m_target;

	Ship() : m_pos({ 0.0f, 0.0f }), m_vel({ 0.0f, 0.0f }), m_dir({ 0.0f, 0.0f }), m_target({0.0f, 0.0f}), m_acc(0.0f) {}

	void update(Ship* enemy_ships, float deltaTime);

private:

	float tts(float deltaTime) const;
	float tta(float deltaTime) const;

	void update_position(float deltaTime);
};

