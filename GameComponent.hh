#pragma once

#include "Vector2.hh"

namespace game {

enum GameComponentType {
	LASER, TARGET, MIRROR, BLOCKER
};

struct GameComponent final {
	// x, y position of center of object
	vector::Vector2 pos;
	
	// rotation clockwise from straight up
	float rotation;

	GameComponentType type;
};

}  // namespace game
