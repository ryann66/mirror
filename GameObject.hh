#pragma once

#include "Vector2.hh"

namespace game {

class Kart;

/**
 * Common ancestor for all objects in the game scene
*/
class GameObject {
 public:
	GameObject(vector::Vector2f pos, float rot) : pos(pos), rotation(rot) { }
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	virtual ~GameObject() { }

	/**
	 * displays the object
	*/
	virtual void display(size_t frameCount) = 0;

	/**
	 * Checks for collision and imparts force/movement onto kart if collides
	*/
	virtual void onCollision(Kart&) = 0;

 protected:
	// in map coords
	vector::Vector2f pos;
	
	// in degrees
	float rotation;
};

/**
 * Exclusion class to provide distinction between static and dynamic objects
*/
class StaticGameObject : public GameObject {
 public:
	StaticGameObject(vector::Vector2f pos, float rot) : GameObject(pos, rot) { }
	StaticGameObject(const StaticGameObject&) = delete;
	StaticGameObject& operator=(const StaticGameObject&) = delete;
	virtual ~StaticGameObject() { }

	/**
	 * displays the object
	*/
	virtual void display(size_t frameCount) = 0;

	/**
	 * Checks for collision and imparts force/movement onto kart if collides
	*/
	virtual void onCollision(Kart&) = 0;
};

}  // namespace game