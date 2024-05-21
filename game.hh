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

const float ROTATION_SENSITIVITY = 2.;

const int MAX_LASER_DEPTH = 20;

const vector::Vector2 LASER_SIZE(2, 6);
const vector::Vector2 TARGET_SIZE(4, 4);
const vector::Vector2 DEFAULT_BOARD_SIZE(50, 50);

}  // namespace game