#include "Kart.hh"
#include "kartMechanics.hh"
#include "GameScene.hh"

using vector::Vector2f;

namespace game {

void Kart::display(int frameCount) {

}

void Kart::move() {
	pos += vel;
	rotation += rotVel;
	
	// Align car momentum with car
	// TODO: make algorithm better (variable)
	float speed = vel.magnitude();
	// remove speed in vel direction
	vel *= (1. - TIRE_FRICTION);
	// add speed in car direction
	vel += Vector2f(rotation) * (speed * TIRE_FRICTION);

	// gas pedal
	if (control.gas == GAS) {
		vel += Vector2f(rotation) * ACTUAL_GAS_ACCELERATION;
	} else if (control.gas = BRAKE) {
		vel += Vector2f(rotation) * -ACTUAL_BRAKE_DECCELERATION;
	}
	// drag
	speed = vel.magnitude();
	vel *= (speed - ACTUAL_DRAG) / speed;

	// terrain slowdown
	float maxSpeed = curScene->map->stableSpeed(pos);
	speed = vel.magnitude();
	if (speed > maxSpeed) {
		float newSpeed = fmaxf(maxSpeed, speed * ACTUAL_ROUGHNESS_SLOWDOWN);
		vel *= newSpeed / speed;
	}

	// steering wheel
	if (control.steering == LEFT) rotVel = ACTUAL_TURN_RATE;
	else if (control.steering == RIGHT) rotVel = -ACTUAL_TURN_RATE;
	else rotVel = 0;
}

void Kart::onCollision(Kart& otherKart) {

}

}  // namespace game