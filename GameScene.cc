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
#include "game.hh"

using std::list;

namespace game {

GameScene* curScene;

int changeCount = 0;

void gameWinCheckFunc(int value) {
	if (value != changeCount) return;
	curScene->level->setBeat();
	window->replaceScene(LEVEL_SELECTOR);
}

void gameSceneDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// reset targets
	for (auto& target : curScene->level->targets) {
		target->lasersHit = 0;
	}
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
		// start win timer
		glutTimerFunc(MS_WIN_DELAY, gameWinCheckFunc, changeCount);
	}
	glutSwapBuffers();
}

GameScene::~GameScene() {
	delete Level;
}

void GameScene::onLoad() {
	curScene = this;
	glutDisplayFunc(displayFunction);
	glutPostRedisplay();
}

void GameScene::onUnload() {
	curScene = nullptr;
	glutDisplayFunc(unregisteredDisplayFunc);
}

}  // namespace game
