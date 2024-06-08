#include "GameComponent.hh"
#include "GameScene.hh"
#include "Level.hh"
#include "utils.hh"
#include "game.hh"

using vector::Vector2f;

namespace game {

bool collide(Ray& ray, LineSegment& line, Collision* out) {
	// TODO
	return false;
}

bool Laser::hitboxClicked(int x, int y) {
	// TODO
	return false;
}

bool Laser::collide(Ray& ray, Collision* out) {
	// lasers don't block lasers
	return false;
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

bool Target::hitboxClicked(int x, int y) {
	// TODO
	return false;
}

bool Target::collide(Ray& ray, Collision* out) {
	// TODO
	return false;
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
	glBegin(GL_QUADS);
		glColor4fv(color);
		// left wing
		glVertex2f(levelGlCoordX(pos.x + v1.x), levelGlCoordY(pos.y + v1.y));
		glVertex2f(levelGlCoordX(pos.x + v2.x), levelGlCoordY(pos.y + v2.y));
		glVertex2f(levelGlCoordX(pos.x + v9.x), levelGlCoordY(pos.y + v9.y));
		glVertex2f(levelGlCoordX(pos.x + v5.x), levelGlCoordY(pos.y + v5.y));
		// bottom
		glVertex2f(levelGlCoordX(pos.x + v7.x), levelGlCoordY(pos.y + v7.y));
		glVertex2f(levelGlCoordX(pos.x + v8.x), levelGlCoordY(pos.y + v8.y));
		glVertex2f(levelGlCoordX(pos.x + v10.x), levelGlCoordY(pos.y + v10.y));
		glVertex2f(levelGlCoordX(pos.x + v9.x), levelGlCoordY(pos.y + v9.y));
		// right wing
		glVertex2f(levelGlCoordX(pos.x + v6.x), levelGlCoordY(pos.y + v6.y));
		glVertex2f(levelGlCoordX(pos.x + v4.x), levelGlCoordY(pos.y + v4.y));
		glVertex2f(levelGlCoordX(pos.x + v3.x), levelGlCoordY(pos.y + v3.y));
		glVertex2f(levelGlCoordX(pos.x + v10.x), levelGlCoordY(pos.y + v10.y));
		// reciever color center
		glColor4fv(colorNeeded);
		glVertex2f(levelGlCoordX(pos.x + v5.x), levelGlCoordY(pos.y + v5.y));
		glVertex2f(levelGlCoordX(pos.x + v6.x), levelGlCoordY(pos.y + v6.y));
		glVertex2f(levelGlCoordX(pos.x + v8.x), levelGlCoordY(pos.y + v8.y));
		glVertex2f(levelGlCoordX(pos.x + v7.x), levelGlCoordY(pos.y + v7.y));
	glEnd();
}

bool Blocker::hitboxClicked(int x, int y) {
	// TODO
	return false;
}

bool Blocker::collide(Ray& ray, Collision* out) {
	// TODO
	return false;
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

bool Mirror::hitboxClicked(int x, int y) {
	// TODO
	return false;
}

bool Mirror::collide(Ray& ray, Collision* out) {
	// TODO
	return false;
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
