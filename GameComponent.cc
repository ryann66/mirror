#include "GameComponent.hh"
#include "GameScene.hh"
#include "Level.hh"
#include "utils.hh"

#include <iostream>
using std::cerr;
using std::endl;

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
	float theta = degToRad(-rotation);
	float cos = cosf(theta);
	float sin = sinf(theta);
	int halfWidth = size.x / 2;
	int halfHeight = size.y / 2;
	float newWidth = cos * halfWidth - sin * halfHeight;
	float newHeight = sin * halfWidth + cos * halfHeight;
	glColor4fv(color);
	glBegin(GL_QUADS);
		glVertex2f(levelGlCoordX(pos.x + newWidth), levelGlCoordY(pos.y + newHeight));
		glVertex2f(levelGlCoordX(pos.x + newWidth), levelGlCoordY(pos.y - newHeight));
		glVertex2f(levelGlCoordX(pos.x - newWidth), levelGlCoordY(pos.y - newHeight));
		glVertex2f(levelGlCoordX(pos.x - newWidth), levelGlCoordY(pos.y + newHeight));
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
	float theta = degToRad(-rotation);
	float cos = cosf(theta);
	float sin = sinf(theta);
	int halfWidth = size.x / 2;
	int halfHeight = size.y / 2;
	float newWidth = cos * halfWidth - sin * halfHeight;
	float newHeight = sin * halfWidth + cos * halfHeight;
	glColor4fv(color);
	glBegin(GL_QUADS);
		glVertex2f(levelGlCoordX(pos.x + newWidth), levelGlCoordY(pos.y + newHeight));
		glVertex2f(levelGlCoordX(pos.x + newWidth), levelGlCoordY(pos.y - newHeight));
		glVertex2f(levelGlCoordX(pos.x - newWidth), levelGlCoordY(pos.y - newHeight));
		glVertex2f(levelGlCoordX(pos.x - newWidth), levelGlCoordY(pos.y + newHeight));
	glEnd();
}

}  // namespace game
