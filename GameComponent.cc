#include "GameComponent.hh"

namespace game {

bool collide(Ray& ray, LineSegment& line, Collision* out) {

}

bool Laser::hitboxClicked(int x, int y) {

}

bool Laser::collide(Ray& ray, Collision* out) {
	// lasers don't block lasers
	return false;
}

void Laser::display() {

}

bool Target::hitboxClicked(int x, int y) {

}

bool Target::collide(Ray& ray, Collision* out) {

}

void Target::display() {
	
}

bool Blocker::hitboxClicked(int x, int y) {

}

bool Blocker::collide(Ray& ray, Collision* out) {

}

void Blocker::display() {
	
}

bool Mirror::hitboxClicked(int x, int y) {

}

bool Mirror::collide(Ray& ray, Collision* out) {

}

void Mirror::display() {
	
}

}  // namespace game
