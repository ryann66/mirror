#pragma once

#include <string>

#include "MenuElement.hh"
#include "Vector2.hh"

namespace menu {

/**
 * Generic button
*/
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

/**
 * Simple text button
*/
class EasyButton : public Button {
 public:
	EasyButton(const Anchor, const vector::Vector2 offset, const vector::Vector2 size, std::string text, void (*onClickFunc)()) :
		Button(anchor, offset, size),
		text(text),
		onClickFunc(onClickFunc) { }

	EasyButton(const EasyButton&) = delete;
	EasyButton& operator=(const EasyButton&) = delete;

	/**
	 * Draws this on the current window
	*/
	virtual void display();

	/**
	 * Called when clicked
	*/
	virtual void onClick() { onClickFunc(); }

 private:
	std::string text;
	void (*onClickFunc)();
};

} // namespace menu
