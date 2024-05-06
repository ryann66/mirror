#ifdef __APPLE_CC__
#include <GLUT/gl.h>
#include <GLUT/glu.h>
#include <GLUT/freeglut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include <stdexcept>

#include "Window.hh"

using std::logic_error;

void windowResizeFunc(int w, int h) {
	window->size.x = w;
	window->size.y = h;
	glViewport(0, 0, w, h);
	glutPostRedisplay();
}

Window::Window(Scene* mainScene) : size(1200, 900) {
	glutReshapeFunc(windowResizeFunc);
	activeScene = mainScene->getType();
	scenes[activeScene] = mainScene;
	mainScene->onLoad();
}

Window::~Window() {
	scenes[activeScene]->onUnload();
	for (auto scp : scenes) delete scp.second;
}

void Window::loadScene(SceneType scene) {
	Scene* ns = scenes[scene];
	if (ns == nullptr) throw new logic_error("Attempted to load nonexistent scene");
	scenes[activeScene]->onUnload();
	activeScene = scene;
	ns->onLoad();
}

void Window::addScene(Scene* scene) {
	SceneType type = scene->getType();
	Scene* ex = scenes[type];
	if (ex != nullptr) {
		if (ex->destroyable()) {
			delete ex;
		} else {
			throw new logic_error("Duplicates of scene type");
		}
	}
	scenes[type] = scene;
}

void closeFunction() {
	delete window;
}

void unregisteredDisplayFunc() {
	throw new logic_error("Unregistered display");
}