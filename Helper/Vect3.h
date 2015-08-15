#ifndef VECT3_H
#define VECT3_H
#include <iostream>

namespace ME {

class Vect3i {
public:
	Vect3i();
    Vect3i(const Vect3i &other);
	Vect3i(int _x, int _y, int _z);

	friend std::ostream& operator<<(std::ostream& os, const Vect3i& vec) {
		os << "Vec3i[x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << "]"; 
    	return os;
	}

	friend bool operator==(const Vect3i& vec, const Vect3i& vec2) {
		return ((vec.x == vec2.x) && (vec.y == vec2.y) && (vec.z == vec2.z));
	}

    friend bool operator!=(const Vect3i& vec, const Vect3i& vec2) {
    	return !(vec == vec2);
    }

	int x;
	int y;
	int z;
};

class Vect3f {
public:
	Vect3f();
    Vect3f(const Vect3f &other);
    Vect3f(float _x, float _y, float _z);

	friend std::ostream& operator<<(std::ostream& os, const Vect3f& vec) {
		os << "Vec3f[x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << "]"; 
    	return os;
	}

	friend bool operator==(const Vect3f& vec, const Vect3f& vec2) {
		return ((vec.x == vec2.x) && (vec.y == vec2.y) && (vec.z == vec2.z));
	}

    friend bool operator!=(const Vect3f& vec, const Vect3f& vec2) {
    	return !(vec == vec2);
    }

	float x;
	float y;
	float z;
};

class Vect3d {
public:
	Vect3d();
    Vect3d(const Vect3d &other);
	Vect3d(double _x, double _y, double _z);

	friend std::ostream& operator<<(std::ostream& os, const Vect3d& vec) {
		os << "Vec3d[x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << "]"; 
    	return os;
	}

	friend bool operator==(const Vect3d& vec, const Vect3d& vec2) {
		return ((vec.x == vec2.x) && (vec.y == vec2.y) && (vec.z == vec2.z));
	}

    friend bool operator!=(const Vect3d& vec, const Vect3d& vec2) {
    	return !(vec == vec2);
    }

	double x;
	double y;
	double z;
};


}

#endif
