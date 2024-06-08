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
	float theta = -rotation;
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
	float theta = -rotation;
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
