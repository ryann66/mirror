#include <stdexcept>

#include "MenuElement.hh"
#include "Window.hh"

using vector::Vector2;
using std::logic_error;

namespace menu {

bool MenuElement::inBounds(Vector2 point) {
    Vector2 v(origin());
    if (point.x < v.x || point.y < v.y) return false;
    v = destination();
    if (point.x > v.x || point.y > v.y) return false;
    return true;
}

Vector2 anchorPoint(Anchor anchor) {
    Vector2 point;
    switch (anchor) {
        case LEFT:
        case BOTTOM_LEFT:
        case TOP_LEFT:
            // point.x = 0;
            break;
        case CENTER:
        case BOTTOM:
        case TOP:
            point.x = window->size.x / 2;
            break;
        case RIGHT:
        case BOTTOM_RIGHT:
        case TOP_RIGHT:
            point.x = window->size.x;
            break;
        default:
            throw new logic_error("Unrecognized anchor");
    }
    switch (anchor) {
        case BOTTOM:
        case BOTTOM_LEFT:
        case BOTTOM_RIGHT:
            // point.y = 0;
            break;
        case CENTER:
        case LEFT:
        case RIGHT:
            point.y = window->size.y / 2;
            break;
        case TOP:
        case TOP_LEFT:
        case TOP_RIGHT:
            point.y = window->size.y;
            break;
        default:
            throw new logic_error("Unrecognized anchor");
    }
    return point;
}

vector::Vector2 MenuElement::origin() {
    Vector2 a(anchorPoint(anchor));
    a.x += offset.x - size.x;
    a.y += offset.y - size.y;
}

vector::Vector2 MenuElement::destination() {
    Vector2 a(anchorPoint(anchor));
    a.x += offset.x + size.x;
    a.y += offset.y + size.y;
}

}  // namespace menu