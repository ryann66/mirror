#pragma once

#include <vector>

#include "Vector2.hh"
#include "GameComponent.hh"

namespace game {

/**
 * Game level
*/
struct Level {
	// w, h size of level
	vector::Vector2 size;

	std::vector<GameComponent> components;
};

}  // namespace game