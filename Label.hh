#pragma once

#include <string>

#include "MenuElement.hh"
#include "Vector2.hh"
#include "colors.hh"

namespace menu {

/**
 * Simple text label
 * NOTE: does not free color!
*/
class Label : public MenuElement {
 public:
	Label(const Anchor anchor, const vector::Vector2 offset, const std::string& text, const GLfloat* const color) :
		MenuElement(anchor, offset, vector::Vector2()),
		text(text),
		color(color) { }

	Label(const Label&) = delete;
	Label& operator=(const Label&) = delete;

	/**
	 * Draws this on the current window
	*/
	virtual void display() {
		glColor4fv(color);
		vector::Vector2 an(anchorPoint(anchor));
		displayStringCenter(GLUT_BITMAP_HELVETICA_18, an.x + offset.x, an.y + offset.y + 9, text.c_str());
	}

 private:
	const GLfloat* const color;
	const std::string text;
};

}  // namespace menu