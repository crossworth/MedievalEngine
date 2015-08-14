#include "Vect3.h"

using namespace ME;

Vect3i::Vect3i() {
	x = 0;
	y = 0;
	z = 0;
}

Vect3i::Vect3i(int _x, int _y, int _z) {
	x = _x;
	y = _y;
	z = _z;
}

Vect3f::Vect3f() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vect3f::Vect3f(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

Vect3d::Vect3d() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vect3d::Vect3d(double _x, double _y, double _z) {
	x = _x;
	y = _y;
	z = _z;
}
