#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <list>
#include <iostream>

#include "Vector2.hh"
#include "LineSegment.hh"
#include "GameComponent.hh"

namespace menu {

/**
 * Returns the name of the level when given the filename
 */
std::string levelNameFromFilename(const std::filesystem::path& filename);

/**
 * Comparision operator for comparing level names alphanumerically
 * returns true if lhs < rhs, or if lhs is alphanumerically before rhs
 */
bool cmpAlphabetical(const std::string& lhs, const std::string& rhs);

}

namespace game {

/**
 * Game level
*/
class Level final {
 public:
	/**
	 * reads the level in from file, may produce argument_error* 
	 * if file format is incorrect
	*/
	Level(std::istream& levelfile);
	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;
	~Level() = default;
	
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

	// vector for arbitrary pointers that need to be freed
	std::vector<void*> heapPointers;

	// sets this level to beaten
	void setBeat() { beaten = true; }

 private:
	// traces a ray through the map
	// adds one laser to any targets it collides with
	// modifies ray
	void traceLaser(Ray&, const GLfloat*, std::list<LineSegment>*);

	// marks whether the level has been beat or not
	bool beaten;
};

}  // namespace game