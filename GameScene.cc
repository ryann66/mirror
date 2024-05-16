#ifdef __APPLE_CC__
#include <GLUT/gl.h>
#include <GLUT/glu.h>
#include <GLUT/freeglut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include <list>

#include "GameScene.hh"
#include "Window.hh"

using std::list;

namespace game {

void gameSceneDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto& laser : curScene->level->lasers) {
		// trace laser
		list<LineSegment> path(curScene->level->traceLaser(laser));
		// draw path (TODO)
	}
	for (auto& component : curScene->level->movables) {
		// draw movable objects (TODO)
	}
	for (auto& component : curScene->level->immovables) {
		// draw immovable objects (TODO)
	}
	// check if all the targets are satisfied
	bool complete = true;
	for (auto& target : curScene->level->targets) {
		if (target->lasersHit != target->lasersNeeded) {
			complete = false;
			break;
		}
	}
	if (complete) {
		// start some timer for winning
	}
	glutSwapBuffers();
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
