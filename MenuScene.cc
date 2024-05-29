#ifdef __APPLE_CC__
#include <GLUT/gl.h>
#include <GLUT/glu.h>
#include <GLUT/freeglut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include <fstream>

#include "Window.hh"
#include "MenuScene.hh"
#include "Vector2.hh"
#include "GameScene.hh"
#include "Level.hh"

using vector::Vector2;

namespace menu {

MenuScene* curMenu;

MenuScene::~MenuScene() {
	for (MenuElement* e : elements) delete e;
	for (Button* b : buttons) delete b;
}

/**
 * Handles highlighting buttons when hovered
*/
void hoverFunc(int x, int y) {
	for (Button* b : curMenu->buttons) {
		bool before = b->hovered;
		b->hovered = b->inBounds(vector::Vector2(x, y));
		if (before ^ b->hovered) glutPostRedisplay();
	}
}

/**
 * Handles displaying menu elements
*/
void menuSceneDisplayFunc() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (MenuElement* e : curMenu->elements) e->display();
	for (Button* b : curMenu->buttons) b->display();
	glutSwapBuffers();
}

/**
 * Handles clicking on buttons
*/
void menuSceneClickFunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (Button* b : curMenu->buttons) {
			if (b->inBounds(vector::Vector2(x, y))) b->onClick();
		}
	}
}

void MenuScene::onLoad() {
	for (Button* b : buttons) b->hovered = false;
	glutMotionFunc(hoverFunc);
	glutPassiveMotionFunc(hoverFunc);
	glutMouseFunc(menuSceneClickFunc);
	glutDisplayFunc(displayFunction);
	curMenu = this;
	glutPostRedisplay();
}

void MenuScene::onUnload() {
	glutMotionFunc(nullptr);
	glutPassiveMotionFunc(nullptr);
	glutMouseFunc(nullptr);
	glutDisplayFunc(unregisteredDisplayFunc);
}

/**
 * Enables escape to leave pause menu
*/
void pauseMenuKeyboardFunc(unsigned char key, int x, int y) {
	if (key == 27 /* escape */) window->loadScene(GAME);
}

void PauseMenuScene::onLoad() {
	glutKeyboardFunc(pauseMenuKeyboardFunc);
	MenuScene::onLoad();
}

void PauseMenuScene::onUnload() {
	glutKeyboardFunc(nullptr);
	MenuScene::onUnload();
}

void playButtonClickFunc() {
	std::ifstream gamefile("templevel.txt");
	window->addScene(new game::GameScene(new game::Level(gamefile)));
	window->loadScene(GAME);
}

Scene* mainMenu() {
	MenuScene* main = new MenuScene(MAIN_MENU);
	main->addButton(new EasyButton(CENTER, Vector2(), DEFAULT_BUTTON_SIZE, "Play", playButtonClickFunc));
	return main;
}

Scene* pauseMenu() {
	return nullptr;
}

Scene* levelSelectorMenu() {
	return nullptr;
}

}  // namespace menu