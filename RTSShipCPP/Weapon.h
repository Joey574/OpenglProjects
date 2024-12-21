#pragma once

struct weapon {
	float m_range;
	float m_cooldown;

	float time_since_fired;

	weapon(float range, float cooldown) : m_range(range), m_cooldown(cooldown), time_since_fired(cooldown) {}
};