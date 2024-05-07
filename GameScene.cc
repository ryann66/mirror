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
#include "timings.hh"

namespace game {

GameScene* curScene;

void gameSceneDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	curScene->map->display();
	for (auto k : curScene->karts) k->display(curScene->frameCount);
}

void gameTick(int frame) {
	if (frame < curScene->frameCount) {
		// entered menu
		return;
	}
	if (frame == curScene->frameCount + 1) {
		// skip frame, still calculating previous frame
		glutTimerFunc(MS_PER_FRAME, gameTick, frame);
		return;
	}
	glutTimerFunc(MS_PER_FRAME, gameTick, frame + 1);

	// handle frame
	for (auto k : curScene->karts) k->calculateMove();
	for (auto k : curScene->karts) k->move();
	for (int i = 0; i < curScene->karts.size(); i++) {
		for (int j = i + 1; j < curScene->karts.size(); j++) {
			curScene->karts[i]->onCollision(*curScene->karts[j]);
		}
	}
	for (auto k : curScene->karts) curScene->map->checkCollisions(*k);
	glutPostRedisplay();

	// advance frame count
	curScene->frameCount++;
}

GameScene::~GameScene() {
	delete map;
}

void GameScene::onLoad() {
	curScene = this;
	glutDisplayFunc(displayFunction);
	glutPostRedisplay();
	gameTick(frameCount);
}

void GameScene::onUnload() {
	frameCount += 2;
	glutDisplayFunc(unregisteredDisplayFunc);
}

}  // namespace game
