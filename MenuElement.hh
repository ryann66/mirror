#pragma once

#include "Vector2.hh"

namespace menu {

enum Anchor {
	CENTER, BOTTOM, TOP, LEFT, RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, TOP_LEFT, TOP_RIGHT
};

vector::Vector2 anchorPoint(Anchor anchor);

struct MenuElement {
	MenuElement(const Anchor anchor, const vector::Vector2 offset, const vector::Vector2 size) : 
		anchor(anchor),
		offset(offset),
		size(size) { }

	MenuElement(const MenuElement&) = default;
	MenuElement& operator=(const MenuElement&) = default;

	/**
	 * Returns if the point is inside the menu element
	*/
	bool inBounds(const vector::Vector2 point);

	/**
	 * Draws this on the current window
	*/
	virtual void display() = 0;

	/**
	 * Returns the bottom left (smallest value) corner point
	*/
	vector::Vector2 origin();

	/**
	 * Returns the top right (largest value) corner point
	*/
	vector::Vector2 destination();

	const Anchor anchor;
	const vector::Vector2 offset, size;
};

}  // namespace menu