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
	activeScene = mainScene->type;
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
	SceneType type = scene->type;
	if (scenes[type] != nullptr) throw new logic_error("Duplicates of scene type");
	scenes[type] = scene;
}

void Window::deleteScene(SceneType scene) {
	if (activeScene == scene) throw new logic_error("Cannot delete current scene");
	if (scenes[scene] == nullptr) throw new logic_error("Nonexistent scene");
	delete scenes[scene];
	scenes[scene] = nullptr;

}

void Window::replaceScene(SceneType scene) {
	if (scene == activeScene) throw new logic_error("Cannot replace scene with self");
	SceneType os = activeScene;
	loadScene(scene);
	deleteScene(os);
}

void closeFunction() {
	delete window;
}

void unregisteredDisplayFunc() {
	throw new logic_error("Unregistered display");
}