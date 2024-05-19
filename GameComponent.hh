#pragma once

#include "Vector2.hh"
#include "colors.hh"

namespace game {

enum CollisionType {
	TARGET, MIRROR, BLOCK
};

struct Collision;

struct GameComponent {
	// x, y position of center of object
	vector::Vector2 pos;
	
	// degrees rotation clockwise from straight up
	float rotation;

	/**
	 * Returns true if the given coordinates are inside the hitbox of this
	*/
	virtual bool hitboxClicked(int x, int y) = 0;

	/**
	 * Returns true if the ray originating at origin with direction rot will collide with this
	 * If true, then collision output parameter will be filled out, else it is undefined
	*/
	virtual bool collide(vector::Vector2 origin, float rot, Collision*) = 0;
};

struct Laser : public GameComponent {
	const GLfloat* color;

	virtual bool hitboxClicked(int x, int y) = 0;
	virtual bool collide(vector::Vector2 origin, float rot, Collision*) = 0;
};

struct Target : public GameComponent {
	unsigned int lasersNeeded;
	unsigned int lasersHit;
	
	virtual bool hitboxClicked(int x, int y) = 0;
	virtual bool collide(vector::Vector2 origin, float rot, Collision*) = 0;
};

struct Blocker : public GameComponent {
	vector::Vector2 size;
	
	virtual bool hitboxClicked(int x, int y) = 0;
	virtual bool collide(vector::Vector2 origin, float rot, Collision*) = 0;
};

struct Mirror : public GameComponent {
	vector::Vector2 size;
	
	virtual bool hitboxClicked(int x, int y) = 0;
	virtual bool collide(vector::Vector2 origin, float rot, Collision*) = 0;
};

struct Collision {
	// the object collided with
	GameComponent* collider;
	// the location of the collision
	vector::Vector2 location;
	// distance to the collision
	float distance;
	// type of collision
	CollisionType type;
};

}  // namespace game
