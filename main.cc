#ifdef __APPLE_CC__
#include <GLUT/gl.h>
#include <GLUT/glu.h>
#include <GLUT/freeglut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include "Window.hh"

#define INIT_WINDOW_WIDTH 1200
#define INIT_WINDOW_HEIGHT 900

int main(int argc, char** argv) {
    // initialize glut
    glutInit(&argc, &argv);
    glutInitWindowSize(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT);
    glutInitWindowPos(100, 100);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutCreateWindow("Racer");

    // create window with main menu scene

    // start main loop
    glutMainLoop();
}