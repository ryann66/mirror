#pragma once

#include <vector>
#include <list>

#include "Vector2.hh"
#include "LineSegment.hh"
#include "GameComponent.hh"

namespace game {

/**
 * Game level
*/
struct Level {
	// w, h size of level
	vector::Vector2 size;

	// vector of all movable and immovable components on the board
	// includes lasers
	std::vector<GameComponent*> movables;
	std::vector<GameComponent*> immovables;

	// vector of all lasers
	// lasers should also be placed in either movables or immovables
	std::vector<Laser*> lasers;

	// vector of all targets
	// targets should also be placed in either movables or immovables
	std::vector<Target*> targets;

	// traces a ray through the map
	// adds one laser to any targets it collides with
	std::list<LineSegment> traceLaser(Laser*);

 private:
	// traces a ray through the map
	// adds one laser to any targets it collides with
	std::list<LineSegment> traceLaser(vector::Vector2 origin, float direction);
};

}  // namespace game