#pragma once

#include <string>

#include "MenuElement.hh"
#include "Vector2.hh"

namespace menu {

class Button : public MenuElement {
 public:
	Button(const Anchor anchor, const vector::Vector2 offset, const vector::Vector2 width, void (*buttonDisplayFunc)(), void(*buttonClickFunc)()) :
		MenuElement(anchor, offset, size, buttonDisplayFunc),
		buttonClickFunc(buttonClickFunc) { }

	Button(const Button&) = delete;
	Button& operator=(const Button&) = delete;
	
	// set to whether the button is being hovered over or not by scene
	bool hovered = false;
	
	// called when button clicked
	void (*buttonClickFunc)();
};

void easyButtonDisplayFunc();

class EasyButton : public Button {
 public:
	EasyButton(const Anchor anchor, const vector::Vector2 offset, const vector::Vector2 width, const std::string text, void (*buttonClickFunc)());

	EasyButton(const EasyButton&) = delete;
	EasyButton& operator=(const EasyButton&) = delete;
	
	// button label
	std::string label;
};

// TODO function generators for various buttons

} // namespace menu
