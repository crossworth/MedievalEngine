#include "Area.h"

using namespace ME;

Area::Area(float left, float top, float width, float height) {
    this->left   = left;
    this->top    = top;
    this->width  = width;
    this->height = height;
}

Area::Area(int left, int top, int width, int height) {
    this->left   = static_cast<float>(left);
    this->top    = static_cast<float>(top);
    this->width  = static_cast<float>(width);
    this->height = static_cast<float>(height);
}

bool Area::contains(Vect2f& point, Area& area) {
    float minX = std::min(area.left, area.left + area.width);
    float maxX = std::max(area.left, area.left + area.width);
    float minY = std::min(area.top, area.top + area.height);
    float maxY = std::max(area.top, area.top + area.height);

    return (point.x >= minX) && (point.x < maxX) &&
           (point.y >= minY) && (point.y < maxY);
}

bool Area::contains(Vect2i& point) {
    Vect2f pointFloat(static_cast<float>(point.x), static_cast<float>(point.y));
    return contains(pointFloat);
}

bool Area::intersects(Area& area1, Area& area2) {

    float r1MinX = std::min(area1.left, area1.left + area1.width);
    float r1MaxX = std::max(area1.left, area1.left + area1.width);
    float r1MinY = std::min(area1.top, area1.top + area1.height);
    float r1MaxY = std::max(area1.top, area1.top + area1.height);

    float r2MinX = std::min(area2.left, area2.left + area2.width);
    float r2MaxX = std::max(area2.left, area2.left + area2.width);
    float r2MinY = std::min(area2.top, area2.top + area2.height);
    float r2MaxY = std::max(area2.top, area2.top + area2.height);

    float interLeft   = std::max(r1MinX, r2MinX);
    float interTop    = std::max(r1MinY, r2MinY);
    float interRight  = std::min(r1MaxX, r2MaxX);
    float interBottom = std::min(r1MaxY, r2MaxY);

    if ((interLeft < interRight) && (interTop < interBottom)) {
        return true;
    } else {
        return false;
    }
}

bool Area::contains(Vect2f &point) {
    return Area::contains(point, *this);
}

bool Area::intersects(Area &area) {
    return Area::intersects(area, *this);
}
