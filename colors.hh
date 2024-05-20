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

/**
 * Constant hard coded color values
*/

namespace menu {

const GLfloat EasyButtonDefaultColor[] = {1., 1., 1., 1.};
const GLfloat EasyButtonHoverColor[] = {0.75, 0.75, 0.75, 1.};
const GLfloat EasyButtonTextColor[] = {0., 0., 0., 1.};

}  // namespace menu