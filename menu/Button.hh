#pragma once

#include <string>

#include "MenuElement.hh"
#include "Vector2.hh"

namespace menu {

class Button : public MenuElement {
 public:
	Button(const Anchor anchor, const vector::Vector2 offset, const vector::Vector2 size) :
		MenuElement(anchor, offset, size) { }

	Button(const Button&) = delete;
	Button& operator=(const Button&) = delete;

	/**
	 * Draws this on the current window
	*/
	virtual void display() = 0;

	/**
	 * Called when clicked
	*/
	virtual void onClick() = 0;
	
	// set to whether the button is being hovered over or not by scene
	bool hovered = false;
};

} // namespace menu
