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
using vector::Vector2;

namespace game {

GameScene* curScene;

int changeCount = 0;

/**
 * callback to verify that game didn't change and player has won
*/
void gameSceneWinCheckFunc(int value) {
	if (value != changeCount) return;
	curScene->level->setBeat();
	window->replaceScene(LEVEL_SELECTOR);
}

void gameSceneDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// reset targets
	for (auto target : curScene->level->targets) {
		target->lasersHit = 0;
	}
	for (auto laser : curScene->level->lasers) {
		// trace laser
		list<LineSegment> path(curScene->level->traceLaser(laser));
		// draw path (TODO)
	}
	for (auto component : curScene->level->movables) {
		// draw movable objects (TODO)
	}
	for (auto component : curScene->level->immovables) {
		// draw immovable objects (TODO)
	}
	// check if all the targets are satisfied
	bool complete = true;
	for (auto target : curScene->level->targets) {
		if (target->lasersHit != target->lasersNeeded) {
			complete = false;
			break;
		}
	}
	if (complete) {
		// start win timer
		glutTimerFunc(MS_WIN_DELAY, gameSceneWinCheckFunc, changeCount);
	}
	glutSwapBuffers();
}

bool moveComponent = false, rotateComponent = false;
GameComponent* selected = nullptr;
Vector2 originalPosition;
float originalRotation;
int originalX, originalY;

/**
 * Callback to set and unset which movable is currently being clicked
*/
void gameSceneClickLogger(int button, int state, int x, int y) {
	if (button == MOVE_BUTTON) moveComponent = state == GLUT_DOWN;
	else if (button == ROTATE_BUTTON) rotateComponent = state == GLUT_DOWN;
	else return;

	if (moveComponent == false && rotateComponent == false) selected = nullptr;
	else if (selected == nullptr) {
		// select component
		originalX = x;
		originalY = y;
		for (auto movable : curScene->level->movables) {
			if (movable->hitboxClicked(x, y)) {
				originalPosition = movable->pos;
				originalRotation = movable->rotation;
				selected = movable;
				break;
			}
		}
	}
}

/**
 * Callback to update the position of an element when moving the mouse
*/
void gameSceneDragLogger(int x, int y) {
	// TODO prevent dragging out of scene and prevent overlap (?)
	if (selected == nullptr) return;
	if (MOVE_BUTTON) {
		Vector2 offset(x - originalX, y - originalY);
		selected->pos = originalPosition + offset;
		glutPostRedisplay();
	}
	if (ROTATE_BUTTON) {
		float rotation = originalRotation + (ROTATION_SENSITIVITY * (float)(x - originalX));
		while (rotation > 360.) rotation -= 360.;
		while (rotation < 0.) rotation += 360.;
		selected->rotation = rotation;
		glutPostRedisplay();
	}
}

/**
 * Callback to enable pausing with escape
*/
void gameSceneKeylogger(unsigned char key, int x, int y) {
	if (key == 27 /* escape */) {
		// prevent winning when unloading
		changeCount++;
		window->loadScene(PAUSE_MENU);
	}
}

GameScene::~GameScene() {
	delete level;
}

void GameScene::onLoad() {
	curScene = this;
	glutDisplayFunc(displayFunction);
	glutMouseFunc(gameSceneClickLogger);
	glutMotionFunc(gameSceneDragLogger);
	glutKeyboardFunc(gameSceneKeylogger);
	glutPostRedisplay();
}

void GameScene::onUnload() {
	curScene = nullptr;
	selected = nullptr;
	moveComponent = rotateComponent = false;
	glutMouseFunc(nullptr);
	glutMotionFunc(nullptr);
	glutKeyboardFunc(nullptr);
	glutDisplayFunc(unregisteredDisplayFunc);
}

}  // namespace game
