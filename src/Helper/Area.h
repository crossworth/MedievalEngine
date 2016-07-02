#ifndef AREA_H
#define AREA_H
#include <algorithm>
#include "Helper/Vect2.h"


namespace ME {

class Area {
public:
    Area();
    Area(float left, float top, float width, float height);
    Area(int left, int top, int width, int height);

    inline Area& operator=(const Area& area);

    inline bool operator==(const Area& area2);
    inline bool operator!=(const Area& area2);

    static bool contains(Vect2f& point, Area& area);
    static bool intersects(Area& area1, Area& area2);

    bool contains(Vect2f& point);
    bool contains(Vect2i& point);
    bool intersects(Area& area);

    float left;
    float top;
    float width;
    float height;
};

bool Area::operator==(const Area& area2) {
    return (this->left == area2.left && this->top ==
            area2.top && this->width == area2.width &&
            this->height == area2.height);
}

bool Area::operator!=(const Area& area2) {
    return !(this->left == area2.left && this->top ==
             area2.top && this->width == area2.width &&
             this->height == area2.height);
}

Area& Area::operator=(const Area& area) {
    left   = area.left;
    top    = area.top;
    width  = area.width;
    height = area.height;

    return *this;
}

}

#endif // AREA_H
