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

const GLfloat MenuLabelColor[] = {1., 1., 1., 1.};

}  // namespace menu

namespace game {

const GLfloat MirrorAlpha = 0.7;
const GLfloat BlockerAlpha = 1.0;
const GLfloat LaserBeamAlpha = 0.9;
const GLfloat TargetRecieverAlpha = 1.0;
const GLfloat LaserAlpha = 1.0;
const GLfloat TargetAlpha = 1.0;
const GLfloat BackgroundAlpha = 1.0;

const GLfloat DefaultMirrorColor[] = {0.65, 0.7, 0.8, MirrorAlpha};
const GLfloat DefaultBlockerColor[] = {0.5, 0.5, 0.5, BlockerAlpha};
const GLfloat DefaultLaserColor[] = {0.4, 0.45, 0.45, 1.0};
const GLfloat DefaultTargetColor[] = {0.4, 0.45, 0.45, 1.0};
const GLfloat DefaultBackgroundColor[] = {0., 0., 0., 1.0};

const GLfloat DefaultLaserBeamColor[] = {0.95, 0.05, 0.05, LaserBeamAlpha};
const GLfloat DefaultTargetRecieverColor[] = {0.95, 0.05, 0.05, TargetRecieverAlpha};

}  // namespace game