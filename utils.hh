#pragma once

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

/**
 * Returns the width of the string rendered in the given glut font
*/
int stringWidth(void* font, const char* str);

/**
 * Displays the string
 * Aligns with bottom left at (x,y)
*/
void displayStringLeft(void* font, int x, int y, const char* str);

/**
 * Displays the string
 * Aligns with the center bottom at (x,y)
*/
void displayStringCenter(void* font, int x, int y, const char* str);

/**
 * Displays the string
 * Aligns with bottom right at (x,y)
*/
void displayStringRight(void* font, int x, int y, const char* str);

/**
 * Converts between radians and degrees
*/
inline float radToDeg(float rad) {
	return rad * 180. / M_PI;
}
inline float degToRad(float deg) {
	return deg / 180. * M_PI;
}
