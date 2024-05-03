#pragma once

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
	return ((float)(glutCoordX * 2)) / window->size.x;
}
inline float glCoordSpaceY(int glutCoordY) {
	return ((float)(glutCoordY * -2)) / window->size.y;
}