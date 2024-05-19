#pragma once

#include "Vector2.hh"

/**
 * Two integer points line segment
*/
struct LineSegment {
	LineSegment(vector::Vector2f s, vector::Vector2f e) : start(s), end(e) { }
	LineSegment(float sx, float sy, float ex, float ey) : start(sx, sy), end(ex, ey) { }
	LineSegment(const LineSegment&) = default;
	LineSegment& operator=(const LineSegment&) = default;

	vector::Vector2f start, end;
};

/**
 * Rename of line segment that suggests ray usage
 * Start and end become two points on the ray
*/
typedef LineSegment Ray;