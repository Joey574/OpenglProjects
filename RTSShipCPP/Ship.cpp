#include "Ship.h"

void Ship::update(const std::vector<Ship>& enemy_ships, float deltaTime) {
	update_position(deltaTime);
}

void Ship::update_position(float deltaTime) {
	vec2 delta = { 0.0f, 0.0f };
	
	if (vec2::distance(m_tar, m_pos) > 0.0f) {
		m_dir = m_tar - m_pos;
		delta = vec2::normalized(m_dir) * m_acc;

		delta = tts() >= tta() ? (-delta) : (delta);

	} else if (m_vel.x != 0.0f || m_vel.y != 0.0f) {
		delta = -vec2::normalized(m_vel) * m_acc;

		if (std::abs(delta.x * deltaTime) > std::abs(m_vel.x)) { m_vel.x = 0.0f; delta.x = 0.0f; }
		if (std::abs(delta.y * deltaTime) > std::abs(m_vel.y)) { m_vel.y = 0.0f; delta.y = 0.0f; }
	}

	m_vel += delta * deltaTime * 0.5f;
	m_pos += m_vel * deltaTime;
	m_vel += delta * deltaTime * 0.5f;
}
void Ship::fire_actions(float deltaTime) {

}

float Ship::tts() const {
	return (vec2::magnitude(m_vel)) / (m_acc);
}
float Ship::tta() const {
	float time = vec2::distance(m_pos, m_tar) / (vec2::magnitude(m_vel));
	float theta = vec2::angle(m_vel, m_tar - m_pos);
	time += theta > 1.5707963267948966f ? tts() : 0.0f;
	return time;
}
