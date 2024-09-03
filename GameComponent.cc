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

void GameComponent::display() {
	if (canMove) {
		float theta = rotation;
		Vector2f v3(MOVABLE_INDICATOR_SIZE, MOVABLE_INDICATOR_SIZE / 5.0f);
		Vector2f v1(-v3.x, -v3.y), v2(-v3.x, v3.y), v4(v3.x, -v3.y);
		glColor4fv(MovableIndicatorColor);
		glBegin(GL_QUADS);
			glVertex2f(levelGlCoordX(pos.x + v1.x), levelGlCoordY(pos.y + v1.y));
			glVertex2f(levelGlCoordX(pos.x + v2.x), levelGlCoordY(pos.y + v2.y));
			glVertex2f(levelGlCoordX(pos.x + v3.x), levelGlCoordY(pos.y + v3.y));
			glVertex2f(levelGlCoordX(pos.x + v4.x), levelGlCoordY(pos.y + v4.y));
			v1.rotate(90);
			v2.rotate(90);
			v3.rotate(90);
			v4.rotate(90);
			glVertex2f(levelGlCoordX(pos.x + v1.x), levelGlCoordY(pos.y + v1.y));
			glVertex2f(levelGlCoordX(pos.x + v2.x), levelGlCoordY(pos.y + v2.y));
			glVertex2f(levelGlCoordX(pos.x + v3.x), levelGlCoordY(pos.y + v3.y));
			glVertex2f(levelGlCoordX(pos.x + v4.x), levelGlCoordY(pos.y + v4.y));
		glEnd();
	}
	if (canRotate) {
		glColor4fv(RotatableIndicatorColor);
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f(levelGlCoordX(pos.x), levelGlCoordY(pos.y));
			for(int i = 0; i <= 300; i++){
				double angle = 2 * M_PI * i / 300;
				double x = cos(angle) * ROTATABLE_INDICATOR_SIZE;
				double y = sin(angle) * ROTATABLE_INDICATOR_SIZE;
				glVertex2f(levelGlCoordX(pos.x + x), levelGlCoordY(pos.y + y));
			}
		glEnd();
	}
}

bool collideRay(Ray& ray, LineSegment& line, Collision* out) {
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
	Vector2f clickLocation(x, y);
	clickLocation -= pos;
	clickLocation.rotate(-this->rotation);
	return 2 * fabsf(clickLocation.x) < size.x && 2 * fabsf(clickLocation.y) < size.y;
}

bool Laser::collide(Ray& ray, Collision* out) {
	// lasers don't block lasers
	return false;
}

float Laser::hitboxRadius() {
	return sqrtf(size.x * size.x + size.y * size.y) / 2.0f;
}

void Laser::display() {
	float theta = rotation;
	Vector2f v3(size.x / 2, size.y / 2);
	Vector2f v1(-v3.x, -v3.y), v2(-v3.x, v3.y), v4(v3.x, -v3.y);
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
	GameComponent::display();
}

bool Target::hitboxClicked(float x, float y) {
	Vector2f clickLocation(x, y);
	clickLocation -= pos;
	clickLocation.rotate(-this->rotation);
	return 2 * fabsf(clickLocation.x) < size.x && 2 * fabsf(clickLocation.y) < size.y;
}

bool Target::collide(Ray& ray, Collision* out) {
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

	// check line collisions
	LineSegment l(v1, v2);
	Collision tmp;
	if (collideRay(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
		out->type = BLOCK;
	}
	l.start = v3;
	if (collideRay(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
		out->type = BLOCK;
	}
	l.end = v4;
	if (collideRay(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
		out->type = BLOCK;
	}
	// check inner wall
	l.start = v1 * (1 - RECIEVER_EDGE_WIDTH) + v4 * RECIEVER_EDGE_WIDTH;
	l.end = v4 * (1 - RECIEVER_EDGE_WIDTH) + v1 * RECIEVER_EDGE_WIDTH;
	if (collideRay(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
		out->type = TARGET;
	}
	// don't check inner wall outside target (can't hit anyways)

	return !isinf(out->distance);
}

float Target::hitboxRadius() {
	return sqrtf(size.x * size.x + size.y * size.y) / 2.0f;
}

void Target::display() {
	float theta = rotation;
	Vector2f v3(size.x / 2, size.y / 2);
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
	GameComponent::display();
}

bool Blocker::hitboxClicked(float x, float y) {
	Vector2f clickLocation(x, y);
	clickLocation -= pos;
	clickLocation.rotate(-this->rotation);
	return 2 * fabsf(clickLocation.x) < size.x && 2 * fabsf(clickLocation.y) < size.y;
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
	if (collideRay(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
	}
	l.start = v3;
	if (collideRay(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
	}
	l.end = v4;
	if (collideRay(ray, l, &tmp) && tmp.distance < out->distance) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
	}
	l.start = v1;
	if (collideRay(ray, l, &tmp) && tmp.distance < out->distance) {
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
	GameComponent::display();
}

bool Mirror::hitboxClicked(float x, float y) {
	Vector2f clickLocation(x, y);
	clickLocation -= pos;
	clickLocation.rotate(-this->rotation);
	return 2 * fabsf(clickLocation.x) < size.x && 2 * fabsf(clickLocation.y) < size.y;
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
	if (collideRay(ray, l, &tmp) && tmp.distance < out->distance && tmp.distance > 0.001) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
	}
	l.start = v3;
	if (collideRay(ray, l, &tmp) && tmp.distance < out->distance && tmp.distance > 0.001) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
	}
	l.end = v4;
	if (collideRay(ray, l, &tmp) && tmp.distance < out->distance && tmp.distance > 0.001) {
		out->location = tmp.location;
		out->distance = tmp.distance;
		out->normal = tmp.normal;
	}
	l.start = v1;
	if (collideRay(ray, l, &tmp) && tmp.distance < out->distance && tmp.distance > 0.001) {
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
	GameComponent::display();
}

#include <iostream>
using std::cout;
using std::endl;

/**
 * Checks if two sets of line segments collide using a divider
 * returns true if the shapes collide
 * returns false if the shapes might not collide
 * NOTE: false does not guarantee the shapes do not collide
*/
bool shapesCollide(LineSegment divider, Vector2f left[], Vector2f right[]) {
	Vector2f projLine(divider.start.y - divider.end.y, divider.end.x - divider.start.x);
	projLine.normalize();
	float leftmax;
	float leftmin = leftmax = vector::dot(left[0], projLine);
	float tmp;
	for (int i = 1; i < 4; i++) {
		tmp = vector::dot(left[i], projLine);
		leftmin = std::min(leftmin, tmp);
		leftmax = std::max(leftmax, tmp);
	}
	
	float rightmax;
	float rightmin = rightmax = vector::dot(right[0], projLine);
	for (int i = 1; i < 4; i++) {
		tmp = vector::dot(right[i], projLine);
		rightmin = std::min(rightmin, tmp);
		rightmax = std::max(rightmax, tmp);
	}

	return !((leftmin < rightmin && leftmax < rightmin) || (leftmin > rightmax && leftmax > rightmax));
}

bool componentsCollide(GameComponent* left, GameComponent* right) {
	if ((left->pos - right->pos).magnitude() >= left->hitboxRadius() + right->hitboxRadius()) return false;

	Vector2f v3(left->size.x / 2, left->size.y / 2);
	Vector2f v1(-v3.x, -v3.y), v2(-v3.x, v3.y), v4(v3.x, -v3.y);
	v1.rotate(left->rotation);
	v2.rotate(left->rotation);
	v3.rotate(left->rotation);
	v4.rotate(left->rotation);
	v1 += left->pos;
	v2 += left->pos;
	v3 += left->pos;
	v4 += left->pos;
	Vector2f leftshape[4] = {v1, v2, v3, v4};

	v3.x = right->size.x / 2;
	v3.y = right->size.y / 2;
	v1.x = -v3.x;
	v1.y = -v3.y;
	v2.x = -v3.x;
	v2.y = v3.y;
	v4.x = v3.x;
	v4.y = -v3.y;
	v1.rotate(right->rotation);
	v2.rotate(right->rotation);
	v3.rotate(right->rotation);
	v4.rotate(right->rotation);
	v1 += right->pos;
	v2 += right->pos;
	v3 += right->pos;
	v4 += right->pos;
	Vector2f rightshape[4] = {v1, v2, v3, v4};

	if (!shapesCollide(LineSegment(leftshape[0], leftshape[1]), leftshape, rightshape)) return false;
	if (!shapesCollide(LineSegment(leftshape[1], leftshape[2]), leftshape, rightshape)) return false;
	if (!shapesCollide(LineSegment(leftshape[2], leftshape[3]), leftshape, rightshape)) return false;
	if (!shapesCollide(LineSegment(leftshape[3], leftshape[0]), leftshape, rightshape)) return false;
	if (!shapesCollide(LineSegment(rightshape[0], rightshape[1]), leftshape, rightshape)) return false;
	if (!shapesCollide(LineSegment(rightshape[1], rightshape[2]), leftshape, rightshape)) return false;
	if (!shapesCollide(LineSegment(rightshape[2], rightshape[3]), leftshape, rightshape)) return false;
	if (!shapesCollide(LineSegment(rightshape[3], rightshape[0]), leftshape, rightshape)) return false;
	return true;
}

}  // namespace game
	
