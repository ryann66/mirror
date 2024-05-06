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

void displayStringLeft(int x, int y, const char* str) {
	
}

void displayStringCenter(int x, int y, const char* str) {

}

void displayStringRight(int x, int y, const char* str) {

}