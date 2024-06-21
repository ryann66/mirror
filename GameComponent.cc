#include <limits>
#include <cmath>

#include "GameComponent.hh"
#include "GameScene.hh"
#include "Level.hh"
#include "utils.hh"
#include "game.hh"

using std::isinf;
using std::abs;
using std::copysignf;
using std::numeric_limits;
using vector::Vector2f;

namespace game {

bool collide(Ray& ray, LineSegment& line, Collision* out) {
	float raySlope = (ray.end.y - ray.start.y) / (ray.end.x - ray.start.x);
	float lineSlope = (line.end.y - line.start.y) / (line.end.x - line.start.x);
	if ((isinf(raySlope) && isinf(lineSlope)) || abs(raySlope - lineSlope) < 0.0001) {
		// parallel lines
		return false;
	}

	float interceptX;
	float interceptY;
	if (isinf(raySlope)) {
		interceptX = ray.start.x;
		interceptY = line.start.y + lineSlope * (interceptX - line.start.x);
	} else if (isinf(lineSlope)) {
		interceptX = line.start.x;
		interceptY = ray.start.y + raySlope * (interceptX - ray.start.x);
	} else {
		interceptX = (ray.start.y + lineSlope * line.start.x - line.start.y - raySlope * ray.start.x) / (lineSlope - raySlope);
		interceptY = line.start.y + lineSlope * (interceptX - line.start.x);
	}

	if (!((interceptX < line.start.x ^ interceptX <= line.end.x) && (interceptY < line.start.y ^ interceptY <= line.end.y))) {
		// out of bounds of line
		return false;
	}

	if (!((interceptX <= ray.start.x ^ ray.start.x < ray.end.x) && (interceptY <= ray.start.y ^ ray.start.y < ray.end.y))) {
		// out of bounds of ray
		return false;
	}

	out->location.x = interceptX;
	out->location.y = interceptY;
	Vector2f normal(line.end);
	normal -= line.start;
	normal.rotate(90);
	if (vector::dot(normal, ray.end - ray.start) > 0) normal *= -1;
	out->normal = normal;
	out->distance = (ray.start - out->location).magnitude();
	return true;
}

bool Laser::hitboxClicked(float x, float y) {
	x -= pos.x;
	y -= pos.y;
	if (sqrtf(x * x + y * y) > hitboxRadius()) return false;
	// TODO
	return true;
}

bool Laser::collide(Ray& ray, Collision* out) {
	// lasers don't block lasers
	return false;
}

float Laser::hitboxRadius() {
	float height = LASER_SIZE.y * LASER_EMITTER_BACKSET;
	return sqrtf(LASER_SIZE.x * LASER_SIZE.x + height * height);
}

void Laser::display() {
	float theta = rotation;
	Vector2f v3(LASER_SIZE.x / 2, LASER_SIZE.y * (2.0f * LASER_EMITTER_BACKSET - 1.0f));
	Vector2f v1(-v3.x, v3.y - LASER_SIZE.y), v2(-v3.x, v3.y), v4(v3.x, v3.y - LASER_SIZE.y);
	v1.rotate(theta);
	v2.rotate(theta);
	v3.rotate(theta);
	v4.rotate(theta);
	glColor4fv(color);
	glBegin(GL_QUADS);
		glVertex2f(levelGlCoordX(pos.x + v1.x), levelGlCoordY(pos.y + v1.y));
		glVertex2f(levelGlCoordX(pos.x + v2.x), levelGlCoordY(pos.y + v2.y));
		glVertex2f(levelGlCoordX(pos.x + v3.x), levelGlCoordY(pos.y + v3.y));
		glVertex2f(levelGlCoordX(pos.x + v4.x), levelGlCoordY(pos.y + v4.y));
	glEnd();
}

bool Target::hitboxClicked(float x, float y) {
	x -= pos.x;
	y -= pos.y;
	if (sqrtf(x * x + y * y) > hitboxRadius()) return false;
	// TODO
	return true;
}

bool Target::collide(Ray& ray, Collision* out) {
	// setup corner points
	float theta = rotation;
	Vector2f v3(TARGET_SIZE.x / 2, TARGET_SIZE.y / 2);
	Vector2f v1(-v3.x, -v3.y), v2(-v3.x, v3.y), v4(v3.x, -v3.y);
	v1.rotate(theta);
	v2.rotate(theta);
	v3.rotate(theta);
	v4.rotate(theta);
	v1 += pos;
	v2 += pos;
	v3 += pos;
	v4 += pos;
	
	// setup output param
	out->distance = numeric_limits<float>::infinity();
	out->collider = this;

	// check line collisions
	LineSegment l(v1, v2);
	Collision tmp;
	if (game::collide(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
		out->type = BLOCK;
	}
	l.start = v3;
	if (game::collide(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
		out->type = BLOCK;
	}
	l.end = v4;
	if (game::collide(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
		out->type = BLOCK;
	}
	// check inner wall
	l.start = v1 * (1 - RECIEVER_EDGE_WIDTH) + v4 * RECIEVER_EDGE_WIDTH;
	l.end = v4 * (1 - RECIEVER_EDGE_WIDTH) + v1 * RECIEVER_EDGE_WIDTH;
	if (game::collide(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
		out->type = TARGET;
		// increment lasers hit
		this->lasersHit++;
	}
	// don't check inner wall outside target (can't hit anyways)

	return !isinf(out->distance);
}

float Target::hitboxRadius() {
	return sqrtf(TARGET_SIZE.x * TARGET_SIZE.x + TARGET_SIZE.y * TARGET_SIZE.y) / 2.0f;
}

void Target::display() {
	float theta = rotation;
	Vector2f v3(TARGET_SIZE.x / 2, TARGET_SIZE.y / 2);
	Vector2f v1(-v3.x, -v3.y), v2(-v3.x, v3.y), v4(v3.x, -v3.y);
	v1.rotate(theta);
	v2.rotate(theta);
	v3.rotate(theta);
	v4.rotate(theta);
	Vector2f v5(v1 * (1 - RECIEVER_EDGE_WIDTH) + v4 * RECIEVER_EDGE_WIDTH);
	Vector2f v6(v4 * (1 - RECIEVER_EDGE_WIDTH) + v1 * RECIEVER_EDGE_WIDTH);
	Vector2f v9(v2 * (1 - RECIEVER_EDGE_WIDTH) + v3 * RECIEVER_EDGE_WIDTH);
	Vector2f v10(v3 * (1 - RECIEVER_EDGE_WIDTH) + v2 * RECIEVER_EDGE_WIDTH);
	Vector2f v7(v5 * (1 - RECIEVER_OPENING_DEPTH) + v9 * RECIEVER_OPENING_DEPTH);
	Vector2f v8(v6 * (1 - RECIEVER_OPENING_DEPTH) + v10 * RECIEVER_OPENING_DEPTH);
	v1 += pos;
	v2 += pos;
	v3 += pos;
	v4 += pos;
	v5 += pos;
	v6 += pos;
	v7 += pos;
	v8 += pos;
	v9 += pos;
	v10 += pos;
	glBegin(GL_QUADS);
		glColor4fv(color);
		// left wing
		glVertex2f(levelGlCoordX(v1.x), levelGlCoordY(v1.y));
		glVertex2f(levelGlCoordX(v2.x), levelGlCoordY(v2.y));
		glVertex2f(levelGlCoordX(v9.x), levelGlCoordY(v9.y));
		glVertex2f(levelGlCoordX(v5.x), levelGlCoordY(v5.y));
		// bottom
		glVertex2f(levelGlCoordX(v7.x), levelGlCoordY(v7.y));
		glVertex2f(levelGlCoordX(v8.x), levelGlCoordY(v8.y));
		glVertex2f(levelGlCoordX(v10.x), levelGlCoordY(v10.y));
		glVertex2f(levelGlCoordX(v9.x), levelGlCoordY(v9.y));
		// right wing
		glVertex2f(levelGlCoordX(v6.x), levelGlCoordY(v6.y));
		glVertex2f(levelGlCoordX(v4.x), levelGlCoordY(v4.y));
		glVertex2f(levelGlCoordX(v3.x), levelGlCoordY(v3.y));
		glVertex2f(levelGlCoordX(v10.x), levelGlCoordY(v10.y));
		// reciever color center
		glColor4fv(colorNeeded);
		glVertex2f(levelGlCoordX(v5.x), levelGlCoordY(v5.y));
		glVertex2f(levelGlCoordX(v6.x), levelGlCoordY(v6.y));
		glVertex2f(levelGlCoordX(v8.x), levelGlCoordY(v8.y));
		glVertex2f(levelGlCoordX(v7.x), levelGlCoordY(v7.y));
	glEnd();
}

bool Blocker::hitboxClicked(float x, float y) {
	x -= pos.x;
	y -= pos.y;
	if (sqrtf(x * x + y * y) > hitboxRadius()) return false;
	// TODO
	return true;
}

bool Blocker::collide(Ray& ray, Collision* out) {
	// setup corner points
	float theta = rotation;
	Vector2f v3(size.x / 2, size.y / 2);
	Vector2f v1(-v3.x, -v3.y), v2(-v3.x, v3.y), v4(v3.x, -v3.y);
	v1.rotate(theta);
	v2.rotate(theta);
	v3.rotate(theta);
	v4.rotate(theta);
	v1 += pos;
	v2 += pos;
	v3 += pos;
	v4 += pos;
	
	// setup output param
	out->distance = numeric_limits<float>::infinity();
	out->collider = this;
	out->type = BLOCK;

	// check line collisions
	LineSegment l(v1, v2);
	Collision tmp;
	if (game::collide(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
	}
	l.start = v3;
	if (game::collide(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
	}
	l.end = v4;
	if (game::collide(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
	}
	l.start = v1;
	if (game::collide(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
	}

	return !isinf(out->distance);
}

float Blocker::hitboxRadius() {
	return sqrtf(size.x * size.x + size.y * size.y) / 2.0f;
}

void Blocker::display() {
	float theta = rotation;
	Vector2f halfSize(size.x / 2, size.y / 2);
	glColor4fv(color);
	glBegin(GL_QUADS);
		Vector2f temp(halfSize);
		temp.rotate(theta);
		glVertex2f(levelGlCoordX(pos.x + temp.x), levelGlCoordY(pos.y + temp.y));
		temp.x = -halfSize.x;
		temp.y = halfSize.y;
		temp.rotate(theta);
		glVertex2f(levelGlCoordX(pos.x + temp.x), levelGlCoordY(pos.y + temp.y));
		temp.x = -halfSize.x;
		temp.y = -halfSize.y;
		temp.rotate(theta);
		glVertex2f(levelGlCoordX(pos.x + temp.x), levelGlCoordY(pos.y + temp.y));
		temp.x = halfSize.x;
		temp.y = -halfSize.y;
		temp.rotate(theta);
		glVertex2f(levelGlCoordX(pos.x + temp.x), levelGlCoordY(pos.y + temp.y));
	glEnd();
}

bool Mirror::hitboxClicked(float x, float y) {
	x -= pos.x;
	y -= pos.y;
	if (sqrtf(x * x + y * y) > hitboxRadius()) return false;
	// TODO
	return true;
}

bool Mirror::collide(Ray& ray, Collision* out) {
	// setup corner points
	float theta = rotation;
	Vector2f v3(size.x / 2, size.y / 2);
	Vector2f v1(-v3.x, -v3.y), v2(-v3.x, v3.y), v4(v3.x, -v3.y);
	v1.rotate(theta);
	v2.rotate(theta);
	v3.rotate(theta);
	v4.rotate(theta);
	v1 += pos;
	v2 += pos;
	v3 += pos;
	v4 += pos;
	
	// setup output param
	out->distance = numeric_limits<float>::infinity();
	out->collider = this;
	out->type = MIRROR;

	// check line collisions
	LineSegment l(v1, v2);
	Collision tmp;
	if (game::collide(ray, l, &tmp) && tmp.distance < out->distance && tmp.distance > 0.001) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
	}
	l.start = v3;
	if (game::collide(ray, l, &tmp) && tmp.distance < out->distance && tmp.distance > 0.001) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
	}
	l.end = v4;
	if (game::collide(ray, l, &tmp) && tmp.distance < out->distance && tmp.distance > 0.001) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
	}
	l.start = v1;
	if (game::collide(ray, l, &tmp) && tmp.distance < out->distance && tmp.distance > 0.001) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
	}

	return !isinf(out->distance);
}

float Mirror::hitboxRadius() {
	return sqrtf(size.x * size.x + size.y * size.y) / 2.0f;
}

void Mirror::display() {
	float theta = rotation;
	Vector2f halfSize(size.x / 2, size.y / 2);
	glColor4fv(color);
	glBegin(GL_QUADS);
		Vector2f temp(halfSize);
		temp.rotate(theta);
		glVertex2f(levelGlCoordX(pos.x + temp.x), levelGlCoordY(pos.y + temp.y));
		temp.x = -halfSize.x;
		temp.y = halfSize.y;
		temp.rotate(theta);
		glVertex2f(levelGlCoordX(pos.x + temp.x), levelGlCoordY(pos.y + temp.y));
		temp.x = -halfSize.x;
		temp.y = -halfSize.y;
		temp.rotate(theta);
		glVertex2f(levelGlCoordX(pos.x + temp.x), levelGlCoordY(pos.y + temp.y));
		temp.x = halfSize.x;
		temp.y = -halfSize.y;
		temp.rotate(theta);
		glVertex2f(levelGlCoordX(pos.x + temp.x), levelGlCoordY(pos.y + temp.y));
	glEnd();
}

}  // namespace game
