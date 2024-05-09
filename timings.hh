#pragma once

/**
 * constant hardcoded timing values
*/

namespace game {

// inputs
const unsigned int FRAME_RATE = 60;
const unsigned int TICKS_PER_FRAME = 10;

// derived timings
constexpr const int TICK_RATE = FRAME_RATE * TICKS_PER_FRAME;
constexpr const float MS_PER_FRAME = 1000. / FRAME_RATE;
constexpr const float MS_PER_TICK = 1000. / TICK_RATE;

}  // namespace game