#pragma once

namespace vector {

struct Vector2 {
	Vector2() : x(0), y(0) { }
	Vector2(int x, int y) : x(x), y(y) { }
	Vector2(const Vector2&) = default;
	Vector2& operator=(const Vector2&) = default;

	int x, y;
};

struct Vector2f {
	Vector2f() : x(0.), y(0.) { }
	Vector2f(float x, float y) : x(x), y(y) { }
	Vector2f(const Vector2f&) = default;
	Vector2f& operator=(const Vector2f&) = default;

	float x, y;
};

}  // namespace vector