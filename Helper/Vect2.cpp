#include "Vect2.h"

using namespace ME;

Vect2i::Vect2i() {
	x = 0;
	y = 0;
}

Vect2i::Vect2i(int _x, int _y) {
	x = _x;
	y = _y;
}

Vect2f::Vect2f() {
	x = 0.0f;
	y = 0.0f;
}

Vect2f::Vect2f(float _x, float _y) {
	x = _x;
	y = _y;
}

Vect2d::Vect2d() {
	x = 0.0;
	y = 0.0;
}

Vect2d::Vect2d(double _x, double _y) {
	x = _x;
	y = _y;
}
