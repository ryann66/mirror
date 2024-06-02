#ifdef __APPLE_CC__
#include <GLUT/gl.h>
#include <GLUT/glu.h>
#include <GLUT/freeglut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>

#include "Level.hh"
#include "utils.hh"
#include "game.hh"

using std::list;
using std::istream;
using std::string;
using std::istringstream;
using std::copy;
using std::begin;
using std::end;
using std::getline;
using std::invalid_argument;
using vector::Vector2;
using vector::Vector2f;

namespace game {

Level::Level(istream& levelfile) {
	// load default colors
	copy(begin(DefaultMirrorColor), end(DefaultMirrorColor), begin(mirrorColor));
	copy(begin(DefaultBlockerColor), end(DefaultBlockerColor), begin(blockerColor));
	copy(begin(DefaultLaserColor), end(DefaultLaserColor), begin(laserColor));
	copy(begin(DefaultTargetColor), end(DefaultTargetColor), begin(targetColor));
	copy(begin(DefaultBackgroundColor), end(DefaultBackgroundColor), begin(backgroundColor));
	copy(begin(DefaultWallColor), end(DefaultWallColor), begin(wallColor));

	const GLfloat* curBeamColor = DefaultLaserBeamColor;
	const GLfloat* curRecieverColor = DefaultTargetRecieverColor;

	// read file
	string line;
	while (getline(levelfile, line)) {
		line.append(1, '\r');
		istringstream ss(line);
		string token;
		int movementEnabled;
		getline(ss, token, ',');
		if (token == "SIZE") {
			ss >> size.x;
			ss.get();
			ss >> size.y;
		} else if (token == "COLOR") {
			getline(ss, token, ',');
			float color[3];
			int tmp;
			ss >> tmp;
			color[0] = static_cast<float>(tmp) / 255;
			ss.get();
			ss >> tmp;
			color[1] = static_cast<float>(tmp) / 255;
			ss.get();
			ss >> tmp;
			color[2] = static_cast<float>(tmp) / 255;
			if (token == "BEAM") {
				GLfloat* beamColors = new GLfloat[8];
				heapPointers.push_back(beamColors);
				beamColors[0] = color[0];
				beamColors[1] = color[1];
				beamColors[2] = color[2];
				beamColors[3] = LaserBeamAlpha;
				beamColors[4] = color[0];
				beamColors[5] = color[1];
				beamColors[6] = color[2];
				beamColors[7] = TargetRecieverAlpha;
				curBeamColor = beamColors;
				curRecieverColor = beamColors + 4;
			} else if (token == "WALL") {
				copy(begin(color), end(color), begin(wallColor));
			} else if (token == "BACKGROUND") {
				copy(begin(color), end(color), begin(backgroundColor));
			} else if (token == "MIRROR") {
				copy(begin(color), end(color), begin(mirrorColor));
			} else if (token == "BLOCKER") {
				copy(begin(color), end(color), begin(blockerColor));
			} else if (token == "LASER") {
				copy(begin(color), end(color), begin(laserColor));
			} else if (token == "TARGET") {
				copy(begin(color), end(color), begin(targetColor));
			} else {
				throw new std::invalid_argument("Unknown mirror argument" + line);
			}
		} else if (token == "MIRROR") {
			Mirror* m = new Mirror();
			ss >> m->pos.x;
			ss.get();
			ss >> m->pos.y;
			ss.get();
			ss >> m->rotation;
			ss.get();
			ss >> m->size.x;
			ss.get();
			ss >> m->size.y;
			ss.get();
			ss >> movementEnabled;
			if (movementEnabled) this->movables.push_back(m);
			else this->immovables.push_back(m);
		} else if (token == "BLOCKER") {
			Blocker* b = new Blocker;
			ss >> b->pos.x;
			ss.get();
			ss >> b->pos.y;
			ss.get();
			ss >> b->rotation;
			ss.get();
			ss >> b->size.x;
			ss.get();
			ss >> b->size.y;
			ss.get();
			ss >> movementEnabled;
			if (movementEnabled) this->movables.push_back(b);
			else this->immovables.push_back(b);
		} else if (token == "TARGET") {
			Target* t = new Target();
			ss >> t->pos.x;
			ss.get();
			ss >> t->pos.y;
			ss.get();
			ss >> t->lasersNeeded;
			t->colorNeeded = curRecieverColor;
			ss.get();
			ss >> movementEnabled;
			if (movementEnabled) this->movables.push_back(t);
			else this->immovables.push_back(t);
		} else if (token == "LASER") {
			Laser* l = new Laser();
			ss >> l->pos.x;
			ss.get();
			ss >> l->pos.y;
			ss.get();
			ss >> l->rotation;
			l->color = curBeamColor;
			ss.get();
			ss >> movementEnabled;
			if (movementEnabled) this->movables.push_back(l);
			else this->immovables.push_back(l);
		} else {
			throw new std::invalid_argument("Unknown argument " + line);
		}
		// premature eof
		if (ss.eof()) throw new std::invalid_argument("Line incomplete: " + line);
		while (ss.peek() == '\r') ss.get();
		// remaining characters in string
		if (!ss.eof()) throw new std::invalid_argument("Extra characters in line: " + line);
	}
}

list<LineSegment> Level::traceLaser(Laser* laser) {
	list<LineSegment> lines;
	Ray ray(laser->pos, laser->pos + directionToVector(laser->rotation));
	traceLaser(ray, laser->color, &lines);
	return lines;
}

void Level::traceLaser(Ray& ray, const GLfloat* laserColor, list<LineSegment>* rays) {
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
				traceLaser(ray, laserColor, rays);
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