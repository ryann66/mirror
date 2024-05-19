#include "Level.hh"

using std::list;
using vector::Vector2;

namespace game {

list<LineSegment> Level::traceLaser(Laser* laser) {
	list<LineSegment> lines;
	traceLaser(laser->pos, laser->rotation, &lines);
	return lines;
}

void Level::traceLaser(Vector2 origin, float direction, list<LineSegment>* rays) {
	GameComponent* collide = nullptr;
	bool reflect = false;
	float distance = 0;
	// check collision distances
	for (GameComponent* component : this->immovables) {
		
	}
	for (GameComponent* component : this->movables) {
		
	}

	if (collide == nullptr) {
		// calculate hit on wall
	}

	// add line segment to list of segments

	// do something based on type of collision
}

}  // namespace game