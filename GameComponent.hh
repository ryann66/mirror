#pragma once

#include "Vector2.hh"
#include "colors.hh"

namespace game {

enum GameComponentType {
	LASER, TARGET, MIRROR, BLOCKER
};

struct GameComponent {
	// x, y position of center of object
	vector::Vector2 pos;
	
	// rotation clockwise from straight up
	float rotation;

	GameComponentType type;
};

struct Laser : public GameComponent {
	const GLfloat* color;
};

struct Target : public GameComponent {
	unsigned int lasersNeeded;
	unsigned int lasersHit;
};

}  // namespace game
