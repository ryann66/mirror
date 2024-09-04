#ifdef __APPLE_CC__
#include <GLUT/gl.h>
#include <GLUT/glu.h>
#include <GLUT/freeglut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include <csignal>
#include <limits>

#include "Window.hh"
#include "MenuScene.hh"
#include "LevelSelectorScene.hh"

#define INIT_WINDOW_WIDTH 900
#define INIT_WINDOW_HEIGHT 900

void closeSignalHandler(int ignored) {
	closeFunction();
}

int main(int argc, char** argv) {
	if (!std::numeric_limits<float>::is_iec559) {
		exit(1);
	}

	// setup signal handlers
	signal(SIGTERM, closeSignalHandler);
	signal(SIGINT, closeSignalHandler);

	// initialize glut
	glutInit(&argc, argv);
	glutInitWindowSize(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA);
	glutCreateWindow("Mirror Game");

	// create window with main menu scene
	window = new Window(menu::mainMenu());
	window->addScene(menu::levelSelectorMenu());
	window->addScene(menu::pauseMenu());

	// start main loop
	glutMainLoop();
}