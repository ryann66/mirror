#pragma once

#include <cmath>

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
	 * Creates a unit vector in the given direction (in degrees)
	*/
	Vector2f(float angle) : x(cosf(M_PI * angle / 180.)), y(sinf(M_PI * angle / 180.)) { }

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

	inline Vector2f& operator+=(const Vector2f& r) {
		x += r.x;
		y += r.y;
		return *this;
	}

	inline Vector2f& operator*=(const float r) {
		x *= r;
		y *= r;
		return *this;
	}

	float x, y;
};

inline Vector2f operator+(const Vector2f& l, const Vector2f& r) {
	Vector2f s(l);
	return s += r;
}

inline Vector2f operator*(const Vector2f& l, const float r) {
	Vector2f p(l);
	return p *= r;
}

inline Vector2f operator*(const float l, const Vector2f& r) {
	Vector2f p(r);
	return p *= l;
}

}  // namespace vector