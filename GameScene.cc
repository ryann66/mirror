#ifdef __APPLE_CC__
#include <GLUT/gl.h>
#include <GLUT/glu.h>
#include <GLUT/freeglut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include "GameScene.hh"
#include "Window.hh"

namespace game {

void gameSceneDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameScene::onLoad() {
	curScene = this;
	glutDisplayFunc(displayFunction);
	glutPostRedisplay();
}

void GameScene::onUnload() {
	glutDisplayFunc(unregisteredDisplayFunc);
}

}  // namespace game
