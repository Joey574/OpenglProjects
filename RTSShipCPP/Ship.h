#pragma once

#include "vec2.cpp"

class Ship
{
public:
	vec2 m_pos;
	vec2 m_vel;

	float m_acc;


	void update(Ship* enemy_ships) {
	}
};

