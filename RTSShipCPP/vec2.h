#pragma once

struct vec2 {
	float x;
	float y;

	static inline float magnitude(const vec2& vec) {
		return std::sqrt(vec.x * vec.x + vec.y * vec.y);
	}
	static inline float angle(const vec2& a, const vec2& b) {
		return std::acos(dotprod(normalized(a), normalized(b)));
	}
	static inline float dotprod(const vec2& a, const vec2& b) {
		return a.x * b.x + a.y * b.y;
	}
	static inline float distance(const vec2& a, const vec2& b) {
		return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
	}

	static inline vec2 normalized(const vec2& vec) {
		float mag = magnitude(vec);
		return { vec.x / mag, vec.y / mag };
	}

	inline vec2 operator + (const vec2& a) const {
		return { x + a.x, y + a.y };
	}
	inline vec2 operator - (const vec2& a) const {
		return { x - a.x, y - a.y };
	}
	
	inline vec2 operator += (const vec2& a) {
		x += a.x; y += a.y;
		return *this;
	}


	inline vec2 operator * (float scalar) const {
		return { x * scalar, y * scalar };
	}
	inline vec2 operator *= (float scalar) {
		x *= scalar; y *= scalar;
		return *this;
	}

	inline vec2 operator - () const {
		return { -x, -y };
	}
};
