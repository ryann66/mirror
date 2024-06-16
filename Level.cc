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
using vector::directionToVector;

namespace game {

Level::Level(istream& levelfile) {
	// load default colors
	const GLfloat* curMirrorColor = DefaultMirrorColor;
	const GLfloat* curBlockerColor = DefaultBlockerColor;
	const GLfloat* curLaserColor = DefaultLaserColor;
	const GLfloat* curTargetColor = DefaultTargetColor;
	const GLfloat* curBackgroundColor = DefaultBackgroundColor;
	const GLfloat* curBeamColor = DefaultLaserBeamColor;
	const GLfloat* curRecieverColor = DefaultTargetRecieverColor;

	// read file
	string line;
	while (getline(levelfile, line)) {
		if (line[0] == '#') continue;
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
			float* color = new float[4];
			heapPointers.push_back(color);
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
				float* color2 = new float[4];
				for (int i = 0; i < 3; i++) color2[i] = color[i];
				heapPointers.push_back(color2);
				color[3] = LaserBeamAlpha;
				curBeamColor = color;
				color2[3] = TargetRecieverAlpha;
				curRecieverColor = color2;
			} else if (token == "BACKGROUND") {
				color[3] = BackgroundAlpha;
				curBackgroundColor = color;
			} else if (token == "MIRROR") {
				color[3] = MirrorAlpha;
				curMirrorColor = color;
			} else if (token == "BLOCKER") {
				color[3] = BlockerAlpha;
				curBlockerColor = color;
			} else if (token == "LASER") {
				color[3] = LaserAlpha;
				curLaserColor = color;
			} else if (token == "TARGET") {
				color[3] = TargetAlpha;
				curTargetColor = color;
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
			m->color = curMirrorColor;
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
			b->color = curBlockerColor;
			if (movementEnabled) this->movables.push_back(b);
			else this->immovables.push_back(b);
		} else if (token == "TARGET") {
			Target* t = new Target();
			ss >> t->pos.x;
			ss.get();
			ss >> t->pos.y;
			ss.get();
			ss >> t->rotation;
			ss.get();
			ss >> t->lasersNeeded;
			t->colorNeeded = curRecieverColor;
			t->color = curTargetColor;
			ss.get();
			ss >> movementEnabled;
			if (movementEnabled) this->movables.push_back(t);
			else this->immovables.push_back(t);
			this->targets.push_back(t);
		} else if (token == "LASER") {
			Laser* l = new Laser();
			ss >> l->pos.x;
			ss.get();
			ss >> l->pos.y;
			ss.get();
			ss >> l->rotation;
			l->beamColor = curBeamColor;
			l->color = curLaserColor;
			ss.get();
			ss >> movementEnabled;
			if (movementEnabled) this->movables.push_back(l);
			else this->immovables.push_back(l);
			this->lasers.push_back(l);
		} else {
			throw new std::invalid_argument("Unknown argument " + line);
		}
		// premature eof
		if (ss.eof()) throw new std::invalid_argument("Line incomplete: " + line);
		// pop \r characters to support CRLF newlines
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
	bool col = false;
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
		shortCol.type = BLOCK;
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
				// direction back towards where current ray was
				Vector2f l(ray.start - ray.end);
				l.normalize();
				shortCol.normal.normalize();
				ray.start = shortCol.location;
				ray.end = (2. * vector::dot(l, shortCol.normal) * shortCol.normal) - l + ray.start;
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