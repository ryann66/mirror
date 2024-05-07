#pragma once

#include "GameObject.hh"

namespace game {

/**
 * Class for karts; inherit to implement controls
 * loop: calculateMove, move, checkCollisions, display
*/
class Kart : public GameObject {
 public:
	Kart(vector::Vector2f pos, float rot) : GameObject(pos, rot) { }
	Kart(const Kart&) = delete;
	Kart& operator=(const Kart&) = delete;
	virtual ~Kart() { }

	/**
	 * displays the kart
	*/
	virtual void display(size_t frameCount);

	/**
	 * Updates the karts position
	*/
	void move();

	/**
	 * Calculates where the kart should go
	 * Implementations may vary based on kart control behavior
	*/
	void calculateMove() = 0;

	/**
	 * Checks for collision and imparts force/movement onto both karts if collides
	*/
	virtual bool onCollision(Kart&);

	int lapCount = 0;

 protected:
	vector::Vector2f vel;
	float rotVel;
};

}  // namespace game