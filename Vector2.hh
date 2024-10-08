#pragma once

#include <cmath>

#include "utils.hh"

namespace vector {

struct Vector2 {
	Vector2() : x(0), y(0) { }
	Vector2(int x, int y) : x(x), y(y) { }
	Vector2(const Vector2&) = default;
	Vector2& operator=(const Vector2&) = default;

	inline Vector2& operator+=(const Vector2& r) {
		x += r.x;
		y += r.y;
		return *this;
	}

	inline Vector2& operator-=(const Vector2& r) {
		x -= r.x;
		y -= r.y;
		return *this;
	}

	inline Vector2& operator*=(const int r) {
		x *= r;
		y *= r;
		return *this;
	}

	int x, y;
};

inline Vector2 operator+(const Vector2& l, const Vector2& r) {
	Vector2 s(l);
	return s += r;
}

inline Vector2 operator-(const Vector2& l, const Vector2& r) {
	Vector2 s(l);
	return s -= r;
}

inline Vector2 operator*(const Vector2& l, const int r) {
	Vector2 p(l);
	return p *= r;
}

inline Vector2 operator*(const int l, const Vector2& r) {
	Vector2 p(r);
	return p *= l;
}

struct Vector2f {
	/**
	 * Creates a static (zero) vector
	*/
	Vector2f() : x(0.), y(0.) { }

	/**
	 * Creates a vector with the given magnitudes x, y
	*/
	Vector2f(float x, float y) : x(x), y(y) { }
	Vector2f(const Vector2f&) = default;
	Vector2f& operator=(const Vector2f&) = default;

	/**
	 * Returns the magnitude of the vector
	*/
	inline float magnitude() const {
		return sqrtf(x * x + y * y);
	}

	inline void normalize() {
		float mag = magnitude();
		x /= mag;
		y /= mag;
	}

	inline Vector2f& operator+=(const Vector2f& r) {
		x += r.x;
		y += r.y;
		return *this;
	}

	inline Vector2f& operator-=(const Vector2f& r) {
		x -= r.x;
		y -= r.y;
		return *this;
	}

	inline Vector2f& operator*=(const float r) {
		x *= r;
		y *= r;
		return *this;
	}

	inline Vector2f& rotate(float deg) {
		float theta = degToRad(deg);
		float cos = cosf(theta);
		float sin = sinf(theta);
		float ox = x, oy = y;
		x = cos * ox - sin * oy;
		y = sin * ox + cos * oy;
		return *this;
	}

	float x, y;
};

inline Vector2f operator+(const Vector2f& l, const Vector2f& r) {
	Vector2f s(l);
	return s += r;
}

inline Vector2f operator-(const Vector2f& l, const Vector2f& r) {
	Vector2f s(l);
	return s -= r;
}

inline Vector2f operator*(const Vector2f& l, const float r) {
	Vector2f p(l);
	return p *= r;
}

inline Vector2f operator*(const float l, const Vector2f& r) {
	Vector2f p(r);
	return p *= l;
}

inline float dot(const Vector2f& l, const Vector2f& r) {
	return l.x * r.x + l.y * r.y;
}

/**
 * Converts a float direction (0 degrees as north) to a vector in glut coordinates (inverted y axis)
*/
inline Vector2f directionToVector(float direction) {
	return Vector2f(sinf(degToRad(direction)), -cosf(degToRad(direction)));
}

/**
 * Converts a vector to a float direction
*/
inline float vectorToDirection(Vector2f vector) {
	float rad;
	if (vector.x >= 0) {
		if (vector.y >= 0) {
			rad = atan2f(vector.x, vector.y);
		} else {
			rad = 180. - atan2f(vector.x, vector.y);
		}
	} else {
		if (vector.y >= 0) {
			rad = 180. + atan2f(vector.x, vector.y);
		} else {
			rad = 360. - atan2f(vector.x, vector.y);
		}
	}
	float r = radToDeg(rad);
	while (r >= 360) r -= 360;
	while (r < 0) r += 360;
	return r;
}

}  // namespace vector