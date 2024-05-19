#pragma once

#include <cmath>

#include "Window.hh"

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
 * Converts X/Y coords from glut coordinate system to gl coordinate system
*/
inline float glCoordSpaceX(int glutCoordX) {
	return (((float)(glutCoordX * 2)) / window->size.x) - 1.;
}
inline float glCoordSpaceY(int glutCoordY) {
	return (((float)(glutCoordY * -2)) / window->size.y) + 1.;
}

/**
 * Converts between radians and degrees
*/
inline float radToDeg(float rad) {
	return rad * 180. / M_PI;
}
inline float degToRad(float deg) {
	return deg / 180. * M_PI;
}

/**
 * Converts a float direction to a vector
*/
inline vector::Vector2f directionToVector(float direction) {
	return vector::Vector2f(sinf(degToRad(direction)), cosf(degToRad(direction)));
}

/**
 * Converts a vector to a float direction
*/
inline float vectorToDirection(vector::Vector2f vector) {
	float rad;
	if (vector.x >= 0) {
		if (vector.y >= 0) {
			rad = atan2f(vector.x, vector.y);
		} else {
			rad = 180. - atan2f(vector.x, vector.y);
		}
	} else {
		if (vector.y >= 0) {
			rad = 180. + atan2f(vector.x, vector.y);
		} else {
			rad = 360. - atan2f(vector.x, vector.y);
		}
	}
	return radToDeg(rad);
}