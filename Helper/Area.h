#ifndef AREA_H
#define AREA_H
#include <Helper/Vect2.h>
#include <algorithm>


namespace ME {

class Area {
public:
    Area(float left, float top, float width, float height);
    Area(int left, int top, int width, int height);

    inline bool operator==(const Area &area2);

    static bool contains(Vect2f &point, Area &area);
    static bool intersects(Area &area1, Area &area2);

    bool contains(Vect2f &point);
    bool contains(Vect2i &point);
    bool intersects(Area &area);

private:
    float left;
    float top;
    float width;
    float height;
};

bool Area::operator==(const Area &area2) {
    return (this->left == area2.left && this->top == area2.top && this->width == area2.width && this->height == area2.height);
}

}

#endif // AREA_H
