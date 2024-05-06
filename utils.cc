#ifdef __APPLE_CC__
#include <GLUT/gl.h>
#include <GLUT/glu.h>
#include <GLUT/freeglut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include "utils.hh"

int stringWidth(void* font, const char* str) {
	int len = 0;
	while (*str) {
		len += glutBitmapWidth(font, static_cast<int>(*str++));
	}
	return len;
}

void displayStringLeft(void* font, int x, int y, const char* str) {
	glRasterPos2i(glCoordSpaceX(x), glCoordSpaceY(y));
	while (*str) {
		glutBitmapCharacter(font, reinterpret_cast<int>(*str++));
	}
}

void displayStringCenter(void* font, int x, int y, const char* str) {
	int left = x - stringWidth(font, str) / 2;
	displayStringLeft(font, left, y, str);
}

void displayStringRight(void* font, int x, int y, const char* str) {
	int left = x - stringWidth(font, str);
	displayStringLeft(font, left, y, str);
}