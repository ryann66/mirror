#ifdef __APPLE_CC__
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cctype>

#include "Level.hh"
#include "utils.hh"
#include "game.hh"
#include "ErrorScene.hh"

using std::list;
using std::istream;
using std::string;
using std::istringstream;
using std::copy;
using std::begin;
using std::end;
using std::getline;
using std::isdigit;
using std::isprint;
using std::toupper;
using std::invalid_argument;
using std::filesystem::path;

using vector::Vector2;
using vector::Vector2f;
using vector::directionToVector;
using menu::newErrorScene;

namespace menu {

string levelNameFromFilename(const path& filename) {
	// get name
	string name(filename.stem().string());
	
	// add a space before each uppercase letter or number
	const char* cname = name.c_str();
	char* cret = new char[name.length() * 2];
	char* cretpnt = cret;
	for (; *cname; cname++) {
		if (!isprint(*cname)) continue;
		if (isupper(*cname)) {
			if (cretpnt[-1] != ' ') *cretpnt++ = ' ';
			*cretpnt++ = *cname;
		} else if (isdigit(*cname)) {
			if (cretpnt[-1] != ' ') *cretpnt++ = ' ';
			do {
				*cretpnt++ = *cname++;
			} while (isdigit(*cname));
			cname--;
			continue;
		} else {
			*cretpnt++ = *cname;
		}

	}

	// cleanup and convert back to string
	*cretpnt = '\0';
	cretpnt = *cret == ' ' ? cret + 1 : cret;
	*cretpnt = toupper(*cretpnt);
	string ret(cret);
	delete[] cret;
	return ret;
}

bool cmpAlphabetical(const string& lhs, const string& rhs) {
	// remove any identical leading characters
	const char* lc = lhs.c_str(), *rc = rhs.c_str();
	while (*lc == *rc) {
		lc++;
		rc++;
	}

	if (isdigit(*lc) && isdigit(*rc)) {
		// sort by number value
		unsigned long long int lint, rint;
		sscanf(lc, "%llu", &lint);
		sscanf(rc, "%llu", &rint);
		return lint < rint;
	} else {
		// sort lexicographically
		return *lc < *rc;
	}
}

}  // namespace menu

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
		int rotationEnabled;
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
				heapPointers.push_back(color2);
				for (int i = 0; i < 3; i++) color2[i] = color[i];
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
				newErrorScene("Unknown mirror argument: " + line);
				return;
			}
		} else if (token == "MIRROR") {
			Mirror* m = new Mirror();
			ss >> m->pos.x;
			ss.get();
			ss >> m->pos.y;
			ss.get();
			ss >> m->rotation;
			ss.get();
			ss >> movementEnabled;
			ss.get();
			ss >> rotationEnabled;
			ss.get();
			ss >> m->size.x;
			ss.get();
			ss >> m->size.y;
			m->color = curMirrorColor;
			m->canMove = static_cast<bool>(movementEnabled);
			m->canRotate = static_cast<bool>(rotationEnabled);
			if (movementEnabled || rotationEnabled) this->movables.push_back(m);
			else this->immovables.push_back(m);
		} else if (token == "BLOCKER") {
			Blocker* b = new Blocker;
			ss >> b->pos.x;
			ss.get();
			ss >> b->pos.y;
			ss.get();
			ss >> b->rotation;
			ss.get();
			ss >> movementEnabled;
			ss.get();
			ss >> rotationEnabled;
			ss.get();
			ss >> b->size.x;
			ss.get();
			ss >> b->size.y;
			b->color = curBlockerColor;
			b->canMove = static_cast<bool>(movementEnabled);
			b->canRotate = static_cast<bool>(rotationEnabled);
			if (movementEnabled || rotationEnabled) this->movables.push_back(b);
			else this->immovables.push_back(b);
		} else if (token == "TARGET") {
			Target* t = new Target();
			t->size = TARGET_SIZE;
			ss >> t->pos.x;
			ss.get();
			ss >> t->pos.y;
			ss.get();
			ss >> t->rotation;
			ss.get();
			ss >> movementEnabled;
			ss.get();
			ss >> rotationEnabled;
			ss.get();
			ss >> t->lasersNeeded;
			t->colorNeeded = curRecieverColor;
			t->color = curTargetColor;
			t->canMove = static_cast<bool>(movementEnabled);
			t->canRotate = static_cast<bool>(rotationEnabled);
			if (movementEnabled || rotationEnabled) this->movables.push_back(t);
			else this->immovables.push_back(t);
			this->targets.push_back(t);
		} else if (token == "LASER") {
			Laser* l = new Laser();
			l->size = LASER_SIZE;
			ss >> l->pos.x;
			ss.get();
			ss >> l->pos.y;
			ss.get();
			ss >> l->rotation;
			ss.get();
			ss >> movementEnabled;
			ss.get();
			ss >> rotationEnabled;
			l->beamColor = curBeamColor;
			l->color = curLaserColor;
			l->canMove = static_cast<bool>(movementEnabled);
			l->canRotate = static_cast<bool>(rotationEnabled);
			if (movementEnabled || rotationEnabled) this->movables.push_back(l);
			else this->immovables.push_back(l);
			this->lasers.push_back(l);
		} else {
			newErrorScene("Unknown argument: " + line);
			return;
		}
		// premature eof
		if (ss.eof()) {
			newErrorScene("Line incomplete: " + line);
			return;
		}
		// pop \r characters to support CRLF newlines
		while (ss.peek() == '\r') ss.get();
		// remaining characters in string
		if (!ss.eof()) {
			newErrorScene("Extra characters in line: " + line);
			return;
		}
	}
}

list<LineSegment> Level::traceLaser(Laser* laser) {
	list<LineSegment> lines;
	Vector2f direction(directionToVector(laser->rotation));
	direction.normalize();
	direction *= LASER_SIZE.y * 0.5f;
	Ray ray(laser->pos + direction, laser->pos + (2 * direction));
	traceLaser(ray, laser->beamColor, &lines);
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
		if (!collideRay(ray, wall, &shortCol)) {
			wall.end = Vector2f(0, size.y);
			if (!collideRay(ray, wall, &shortCol)) {
				wall.start = Vector2f(size.x, size.y);
				if (!collideRay(ray, wall, &shortCol)) {
					wall.end = Vector2f(size.x, 0);
					collideRay(ray, wall, &shortCol);
				}
			}
		}
	}

	// add line segment to list of segments
	rays->emplace_back(ray.start, shortCol.location);

	// do something based on type of collision
	switch (shortCol.type) {
		case MIRROR:
			{
				if (rays->size() == MAX_LASER_DEPTH) return;
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