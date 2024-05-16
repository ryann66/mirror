#pragma once

#include "Vector2.hh"

/**
 * Two integer points line segment
*/
struct LineSegment {
	LineSegment(vector::Vector2 s, vector::Vector2 e) : start(s), end(e) { }
	LineSegment(int sx, int sy, int ex, int ey) : start(sx, sy), end(ex, ey) { }
	LineSegment(const LineSegment&) = default;
	LineSegment& operator=(const LineSegment&) = default;

	vector::Vector2 start, end;
};