#ifdef __APPLE_CC__
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

#include "Button.hh"
#include "Window.hh"
#include "utils.hh"
#include "colors.hh"

using std::string;

namespace menu {

void EasyButton::display() {
	if (this->hovered) glColor4fv(EasyButtonHoverColor);
	else glColor4fv(EasyButtonDefaultColor);
	vector::Vector2 ori(origin()), ds(destination());
	glRectf(glCoordSpaceX(ori.x), glCoordSpaceY(ori.y), glCoordSpaceX(ds.x), glCoordSpaceY(ds.y));
	
	glColor4fv(EasyButtonTextColor);
	vector::Vector2 an(anchorPoint(anchor));
	displayStringCenter(GLUT_BITMAP_HELVETICA_18, an.x + offset.x, an.y + offset.y + 9, text.c_str());
}

}  // namespace menu