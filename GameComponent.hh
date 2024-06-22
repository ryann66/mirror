#pragma once

#include "Vector2.hh"
#include "colors.hh"
#include "LineSegment.hh"

namespace game {

enum CollisionType {
	TARGET, MIRROR, BLOCK
};

struct Collision;

/**
 * Checks for a collision of the ray with the line segment
 * Returns true and fills out parameter on collision, else returns false (out is undefined)
 * Never fills out collider and type fields of out!
 * NOTE: rays cannot collide in reverse, out.distance will always be positive
*/
bool collideRay(Ray& ray, LineSegment& line, Collision* out);

struct GameComponent {
	// x, y position of center of object
	vector::Vector2f pos;
	
	// degrees rotation clockwise from straight up
	float rotation;

	/**
	 * Returns true if the given level coordinates are inside the hitbox of this
	*/
	virtual bool hitboxClicked(float x, float y) = 0;

	/**
	 * Returns true if the ray originating at origin with direction rot will collide with this
	 * If true, then collision output parameter will be filled out, else it is undefined
	*/
	virtual bool collide(Ray& ray, Collision* out) = 0;

	/**
	 * Draws the object on the screen
	*/
	virtual void display() = 0;
};

struct Laser : public GameComponent {
	const GLfloat* color;
	const GLfloat* beamColor;

	virtual bool hitboxClicked(float x, float y);
	virtual bool collide(Ray& ray, Collision* out);
	virtual void display();
};

struct Target : public GameComponent {
	const GLfloat* color;
	const GLfloat* colorNeeded;
	unsigned int lasersNeeded;
	unsigned int lasersHit;
	
	virtual bool hitboxClicked(float x, float y);
	virtual bool collide(Ray& ray, Collision* out);
	virtual void display();
};

struct Blocker : public GameComponent {
	const GLfloat* color;
	vector::Vector2 size;
	
	virtual bool hitboxClicked(float x, float y);
	virtual bool collide(Ray& ray, Collision* out);
	virtual void display();
};

struct Mirror : public GameComponent {
	const GLfloat* color;
	vector::Vector2 size;
	
	virtual bool hitboxClicked(float x, float y);
	virtual bool collide(Ray& ray, Collision* out);
	virtual void display();
};

struct Collision {
	// the object collided with
	GameComponent* collider;
	// the location of the collision
	vector::Vector2f location;
	// distance to the collision
	float distance;
	// type of collision
	CollisionType type;
	// normal of collision plane
	vector::Vector2f normal;
};

}  // namespace game
