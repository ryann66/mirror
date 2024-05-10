#pragma once

#include "GameObject.hh"

namespace game {

/**
 * Struct for controlling how the kart should move
*/
struct KartControls {
	enum {
		BRAKE, IDLE, GAS
	} gas;
	enum {
		LEFT, STRAIGHT, RIGHT
	} steering;
};

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
	virtual void display(int frameCount);

	/**
	 * Updates the karts position
	*/
	void move();

	/**
	 * Calculates where the kart should go
	 * Implementations may vary based on kart control behavior
	*/
	virtual void calculateMove() = 0;

	/**
	 * Checks for collision and imparts force/movement onto both karts if collides
	*/
	virtual void onCollision(Kart&);

	int lapCount = 0;

	const vector::Vector2f boundingSize = {3., 5.};

 protected:
	vector::Vector2f vel;
	float rotVel;
	KartControls control;
};

}  // namespace game