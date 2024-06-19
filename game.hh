#pragma once

#ifdef __APPLE_CC__
#include <GLUT/gl.h>
#include <GLUT/glu.h>
#include <GLUT/freeglut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include "Vector2.hh"

namespace game {

const unsigned int MS_WIN_DELAY = 1500;

const int MOVE_BUTTON = GLUT_LEFT_BUTTON;
const int ROTATE_BUTTON = GLUT_RIGHT_BUTTON;

const float ROTATION_SENSITIVITY = 0.5f;

// max recursive depth of lasers
const int MAX_LASER_DEPTH = 20;

// size of the laser and target components (fixed)
const vector::Vector2 LASER_SIZE(15, 30);
const vector::Vector2 TARGET_SIZE(50, 15);

// default size of the board, can be overridden by levels
const vector::Vector2 DEFAULT_BOARD_SIZE(200, 200);

// width of the laser beam
const float LASER_WIDTH = 1.0f;

// percentage dimensions of the opening of the reciever
const constexpr float RECIEVER_OPENING_WIDTH = 0.8f;
const constexpr float RECIEVER_OPENING_DEPTH = 0.5f;

// Percentage of reciever front taken up by the side wall
const constexpr float RECIEVER_EDGE_WIDTH = (1.0f - RECIEVER_OPENING_WIDTH) / 2.0f;

// percentage of laser emitter that is behind the pivot
const float LASER_EMITTER_BACKSET = 0.8f;

// scale to render drawn elements at (does not affect reflections!)
const float ELEMENT_DRAW_SCALE = 1.25f;

}  // namespace game