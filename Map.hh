#pragma once

#include <iostream>
#include <vector>

#include "GameObject.hh"
#include "Vector2.hh"

namespace game {

/**
 * Map class contains the map data and can load it from a file
*/
class Map final {
 public:
	/**
	 * Instantiates the map from the given input stream
	*/
	Map(std::istream& map);
	Map(const Map&) = delete;
	Map& operator=(const Map&) = delete;
	~Map();

	/**
	 * Checks collisions between the given kart and the environment
	*/
	void checkCollisions(Kart&);

	/**
	 * Displays the map
	*/
	void display();

	/**
	 * Returns the stable speed at a certain point on the map
	 * based on the terrain roughness at that point
	*/
	float stableSpeed(vector::Vector2f pos);

 private:
	std::vector<StaticGameObject*> envir;
	/* bitmaps for ground texture and roughness (kart stable speed) */
};

}  // namespace game