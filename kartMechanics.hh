#pragma once

#include "timings.hh"

namespace game {

// controls percentage of velocity that is conformed to rotation
constexpr const float TIRE_FRICTION = 1.;

// in deg/s (idealized), rate at which kart turns
constexpr const float TURN_RATE = 45.;

// deg/tick rate at which kart turns
constexpr const float ACTUAL_TURN_RATE = TURN_RATE / TICK_RATE;

// percentage of speed above terrain cap that is lost per second
constexpr const float ROUGHNESS_SLOWDOWN = 0.5;

// percentage of speed above terrain cap that is lost per tick
constexpr const float ACTUAL_ROUGHNESS_SLOWDOWN = powf(ROUGHNESS_SLOWDOWN, 1. / TICKS_PER_FRAME);

// acceleration per second from gas pedal
constexpr const float GAS_ACCELERATION = 4;

// acceleration per tick
constexpr const float ACTUAL_GAS_ACCELERATION = GAS_ACCELERATION / TICK_RATE;

// decceleration per second from brake pedal
constexpr const float BRAKE_DECCELERATION = 3;

// decceleration per tick
constexpr const float ACTUAL_BRAKE_DECCELERATION = BRAKE_DECCELERATION / TICK_RATE;

// decceleration from drag per second
constexpr const float DRAG = 1;

// decceleration from drag per tick
constexpr const float ACTUAL_DRAG = DRAG / TICK_RATE;

}  // namespace game