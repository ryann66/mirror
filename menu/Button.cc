#include "Button.hh"
#include "Window.hh"
#include "utils.hh"
#include "colors.hh"

using std::string;

namespace menu {

void EasyButton::display() {
	if (this->hovered) glColor4fv(EasyButtonHoverColor);
	else glColor4fv(EasyButtonDefaultColor);
	vector::Vector2 or(origin()), ds(destination());
	glRectf(glCoordSpaceX(or.x), glCoordSpaceY(or.y), glCoordSpaceX(ds.x), glCoordSpaceY(ds.y));
	
	glColor4fv(EasyButtonTextColor);
	vector::Vector2 an(anchorPoint(anchor()));
	displayStringCenter(GLUT_BITMAP_HELVETICA_18, an.x, an.y - 9, text);
}

}  // namespace menu