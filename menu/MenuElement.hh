#pragma once

#include "Vector2.hh"

namespace menu {

enum Anchor {
	CENTER, BOTTOM_LEFT, BOTTOM_RIGHT, TOP_LEFT, TOP_RIGHT
};

struct MenuElement {
	MenuElement(const Anchor anchor, const vector::Vector2 offset, const vector::Vector2 size, void (*displayFunction)()) : 
		anchor(anchor),
		offset(offset),
		size(size),
		displayFunction(displayFunction) { }

	MenuElement(const MenuElement&) = default;
	MenuElement& operator=(const MenuElement&) = default;

	/**
	 * Returns if the point is inside the menu element
	*/
	bool inBounds(const vector::Vector2 point);

	const Anchor anchor;
	const vector::Vector2 offset, size;
	void (*displayFunction)();
};

// TODO function generators for various elements

}  // namespace menu