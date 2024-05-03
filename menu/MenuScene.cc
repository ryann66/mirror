#ifdef __APPLE_CC__
#include <GLUT/gl.h>
#include <GLUT/glu.h>
#include <GLUT/freeglut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include "MenuScene.hh"
#include "Vector2.hh"
#include "timings.hh"

namespace menu {

int menuSceneCounter = 0;
MenuScene* curMenu;

MenuScene::~MenuScene() {
	for (MenuElement* e : elements) delete e;
	for (Button* b : buttons) delete b;
}

void hoverFunc(int x, int y) {
	for (Button* b : curMenu->buttons) {
		bool before = b->hovered;
		b->hovered = b->inBounds(vector::Vector2(x, y));
		if (before ^ b->hovered) glutPostRedisplay();
	}
}

void menuSceneDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (MenuElement* e : curMenu->elements) e->displayFunction();
	for (Button* b : curMenu->buttons) b->displayFunction();
}

void MenuScene::onLoad() {
	for (Button* b : buttons) b->hovered = false;
	glutMotionFunc(hoverFunc);
	glutPassiveMotionFunc(hoverFunc);
	curMenu = this;
	glutPostRedisplay();
}

void MenuScene::onUnload() {
	menuSceneCounter++;
	glutMotionFunc(nullptr);
	glutPassiveMotionFunc(nullptr);
}

}  // namespace menu