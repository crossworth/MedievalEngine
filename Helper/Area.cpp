#include "Area.h"

using namespace ME;

Area::Area(float left, float top, float width, float height) {
    this->left   = left;
    this->top    = top;
    this->width  = width;
    this->height = height;
}

bool Area::contains(Vect2f& point, Area& area) {
    // implements bounds checks
}

bool Area::intersects(Area& area1, Area& area2) {

}

