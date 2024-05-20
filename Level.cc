#ifdef __APPLE_CC__
#include <GLUT/gl.h>
#include <GLUT/glu.h>
#include <GLUT/freeglut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include "Level.hh"
#include "utils.hh"
#include "game.hh"

using std::list;
using std::istream;
using vector::Vector2;
using vector::Vector2f;

namespace game {

Level::Level(istream& levelfile) {

}

list<LineSegment> Level::traceLaser(Laser* laser) {
	list<LineSegment> lines;
	Ray ray(laser->pos, laser->pos + directionToVector(laser->rotation));
	traceLaser(ray, &lines, laser->color);
	return lines;
}

void Level::traceLaser(Ray& ray, list<LineSegment>* rays, const GFloat* laserColor) {
	Collision newCol, shortCol;
	bool col;
	// check collision distances
	for (GameComponent* component : this->immovables) {
		if (col) {
			if (component->collide(ray, &newCol)) {
				if (newCol.distance < shortCol.distance) shortCol = newCol;
			}
		} else {
			col = component->collide(ray, &shortCol);
		}
	}
	for (GameComponent* component : this->movables) {
		if (col) {
			if (component->collide(ray, &newCol)) {
				if (newCol.distance < shortCol.distance) shortCol = newCol;
			}
		} else {
			col = component->collide(ray, &shortCol);
		}
	}

	if (!col) {
		// calculate hit on wall
		LineSegment wall(Vector2f(0, 0), Vector2f(size.x, 0));
		if (!collide(ray, wall, &shortCol)) {
			wall.end = Vector2f(0, size.y);
			if (!collide(ray, wall, &shortCol)) {
				wall.start = Vector2f(size.x, size.y);
				if (!collide(ray, wall, &shortCol)) {
					wall.end = Vector2f(size.x, 0);
					collide(ray, wall, &shortCol);
				}
			}
		}
	}

	// add line segment to list of segments
	rays->emplace_back(ray.start, shortCol.location);

	// do something based on type of collision
	switch (shortCol.type) {
		case MIRROR:
			if (rays->size() == MAX_LASER_DEPTH) return;
			{
				// spawn a recursive call to trace the laser back
				Vector2f v(ray.end - ray.start);
				ray.start = shortCol.location;
				ray.end = (2. * vector::dot(v, shortCol.normal) * shortCol.normal) - v;
				traceLaser(ray, rays, laserColor);
				return;
			}
		case TARGET:
			{
				// add laser hit to target
				Target* target = dynamic_cast<Target*>(shortCol.collider);
				if (target->colorNeeded[0] == laserColor[0] &&
					target->colorNeeded[1] == laserColor[1] &&
					target->colorNeeded[2] == laserColor[2]) {
						target->lasersHit++;
				}
				return;
			}
		case BLOCK:
			return;
	}
}

}  // namespace game