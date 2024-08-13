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
#include "GameComponent.hh"
#include "Window.hh"
#include "game.hh"
#include "utils.hh"

using std::list;
using vector::Vector2;
using vector::Vector2f;

namespace game {

GameScene* curGameScene;

int changeCount = 0;

/**
 * callback to verify that game didn't change and player has won
*/
void gameSceneWinCheckFunc(int value) {
	if (value != changeCount) return;
	if (!curGameScene) return;
	curGameScene->level->setBeat();
	// TODO replace with a win screen
	window->replaceScene(LEVEL_SELECTOR);
}

void gameSceneDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// reset targets
	for (auto target : curGameScene->level->targets) {
		target->lasersHit = 0;
	}
	for (auto laser : curGameScene->level->lasers) {
		// trace laser
		list<LineSegment> path(curGameScene->level->traceLaser(laser));
		glColor4fv(laser->beamColor);
		for (LineSegment& l : path) {
			Vector2f parallel(l.end.x - l.start.x, l.end.y - l.start.y);
			parallel.normalize();
			parallel *= LASER_WIDTH * 0.5f;
			Vector2f normal = Vector2f(-parallel.y, parallel.x);
			glBegin(GL_QUADS);
				glVertex2f(levelGlCoordX(l.start.x - normal.x - parallel.x), levelGlCoordY(l.start.y - normal.y - parallel.y));
				glVertex2f(levelGlCoordX(l.start.x + normal.x - parallel.x), levelGlCoordY(l.start.y + normal.y - parallel.y));
				glVertex2f(levelGlCoordX(l.end.x + normal.x + parallel.x), levelGlCoordY(l.end.y + normal.y + parallel.y));
				glVertex2f(levelGlCoordX(l.end.x - normal.x + parallel.x), levelGlCoordY(l.end.y - normal.y + parallel.y));
			glEnd();
		}
	}
	for (auto component : curGameScene->level->immovables) {
		component->display();
	}
	for (auto component : curGameScene->level->movables) {
		component->display();
	}
	// check if all the targets are satisfied
	for (auto target : curGameScene->level->targets) {
		if (target->lasersHit != target->lasersNeeded) {
			goto incomplete;
		}
	}
	// start win timer
	glutTimerFunc(MS_WIN_DELAY, gameSceneWinCheckFunc, changeCount);
 incomplete:
	glutSwapBuffers();
}

bool moveComponent = false, rotateComponent = false;
GameComponent* selected = nullptr;
Vector2f originalPosition;
Vector2f clickPosition;
float originalRotation;

/**
 * Callback to set and unset which movable is currently being clicked
*/
void gameSceneClickLogger(int button, int state, int x, int y) {
	if (button == MOVE_BUTTON) moveComponent = state == GLUT_DOWN;
	else if (button == ROTATE_BUTTON) rotateComponent = state == GLUT_DOWN;
	else return;

	// convert coordinates to level coordinates
	float levelX = ((float) x) / window->size.x * curGameScene->level->size.x;
	float levelY = ((float) y) / window->size.y * curGameScene->level->size.y;

	if (moveComponent == false && rotateComponent == false) selected = nullptr;
	else if (selected == nullptr) {
		// select component
		for (auto movable : curGameScene->level->movables) {
			if (movable->hitboxClicked(levelX, levelY)) {
				originalPosition = movable->pos;
				originalRotation = movable->rotation;
				selected = movable;
				clickPosition.x = levelX;
				clickPosition.y = levelY;
				break;
			}
		}
	}
}

/**
 * Callback to update the position of an element when moving the mouse
*/
void gameSceneDragLogger(int x, int y) {
	changeCount++;
	if (selected == nullptr) return;
	Vector2f mousePosition(((float) x) / window->size.x * curGameScene->level->size.x, ((float) y) / window->size.y * curGameScene->level->size.y);

	// save current position to revert to
	Vector2f revertPosition(selected->pos);
	float revertRotation = selected->rotation;
	
	// move components
	if (moveComponent && selected->canMove) {
		selected->pos = originalPosition + mousePosition - clickPosition;
		// clamp position to inside walls
		if (selected->pos.x < 0) selected->pos.x = 0;
		else if (selected->pos.x > curGameScene->level->size.x) selected->pos.x = curGameScene->level->size.x;
		if (selected->pos.y < 0) selected->pos.y = 0;
		else if (selected->pos.y > curGameScene->level->size.y) selected->pos.y = curGameScene->level->size.y;
	}
	if (rotateComponent && selected->canRotate) {
		float rotation = originalRotation + (ROTATION_SENSITIVITY * (mousePosition.x - clickPosition.x) + (SECONDARY_ROTATION_SENSITIVITY * (mousePosition.y - clickPosition.y)));
		while (rotation > 360.) rotation -= 360.;
		while (rotation < 0.) rotation += 360.;
		selected->rotation = rotation;
	}

	// check valid position
	for (GameComponent* component : curGameScene->level->immovables) {
		if (componentsCollide(component, selected)) {
			selected->pos = revertPosition;
			selected->rotation = revertRotation;
			return;
		}
	}
	for (GameComponent* component : curGameScene->level->movables) {
		if (component == selected) continue;
		if (componentsCollide(component, selected)) {
			selected->pos = revertPosition;
			selected->rotation = revertRotation;
			return;
		}
	}

	glutPostRedisplay();
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
	curGameScene = this;
	glutDisplayFunc(displayFunction);
	glutMouseFunc(gameSceneClickLogger);
	glutMotionFunc(gameSceneDragLogger);
	glutKeyboardFunc(gameSceneKeylogger);
	glutPostRedisplay();
}

void GameScene::onUnload() {
	curGameScene = nullptr;
	selected = nullptr;
	moveComponent = rotateComponent = false;
	glutMouseFunc(nullptr);
	glutMotionFunc(nullptr);
	glutKeyboardFunc(nullptr);
	glutDisplayFunc(unregisteredDisplayFunc);
}

float levelGlCoordX(float levelCoordX) {
	return ((levelCoordX * 2) / curGameScene->level->size.x) - 1.;
}

float levelGlCoordY(float levelCoordY) {
	return ((levelCoordY * -2) / curGameScene->level->size.y) + 1.;
}

}  // namespace game
