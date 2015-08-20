#ifndef AREA_H
#define AREA_H
#include <Helper/Vect2.h>


namespace ME {

class Area {
public:
    Area(float left, float top, float width, float height);

    static bool contains(Vect2f &point, Area &area);
    static bool intersects(Area &area1, Area &area2);

private:
    float left;
    float top;
    float width;
    float height;
};

}

#endif // AREA_H
