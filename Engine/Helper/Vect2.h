#ifndef VECT2_H
#define VECT2_H
#include <iostream>


namespace ME {

class Vect2f;

class Vect2i {
public:
	Vect2i();

    Vect2i(const Vect2i& other);
    Vect2i(int _x, int _y);
    Vect2i(const Vect2f& other);

    friend std::ostream& operator<<(std::ostream& os,
                                    const Vect2i& vec) {
		os << "Vec2i[x: " << vec.x << ", y: " << vec.y << "]"; 
    	return os;
	}

    inline bool operator==(const Vect2i& vec2) {
        return ((x == vec2.x) && (y == vec2.y));
	}

    inline bool operator!=(const Vect2i& vec2) {
        return !(*this == vec2);
    }

    inline Vect2i operator+(const Vect2i& vec2) {
        return Vect2i(this->x + vec2.x, this->y + vec2.y);
    }

	int x;
	int y;
};

class Vect2f {
public:
	Vect2f();
    Vect2f(const Vect2f& other);
	Vect2f(float _x, float _y);
    Vect2f(const Vect2i& other);

    friend std::ostream& operator<<(std::ostream& os,
                                    const Vect2f& vec) {
		os << "Vec2f[x: " << vec.x << ", y: " << vec.y << "]"; 
    	return os;
	}

    inline bool operator==(const Vect2f& vec2) {
        return ((x == vec2.x) && (y == vec2.y));
	}

    inline bool operator!=(const Vect2f& vec2) {
        return !(*this == vec2);
    }

    inline Vect2f operator+(const Vect2f& vec2) {
        return Vect2f(this->x + vec2.x, this->y + vec2.y);
    }

	float x;
	float y;
};

class Vect2d {
public:
	Vect2d();
    Vect2d(const Vect2d& other);
	Vect2d(double _x, double _y);
    Vect2d(const Vect2i& other);

    friend std::ostream& operator<<(std::ostream& os,
                                    const Vect2d& vec) {
		os << "Vec2d[x: " << vec.x << ", y: " << vec.y << "]"; 
    	return os;
	}

    inline bool operator==(const Vect2d& vec2) {
        return ((x == vec2.x) && (y == vec2.y));
	}

    inline bool operator!=(const Vect2d& vec2) {
        return !(*this == vec2);
    }

    inline Vect2d operator+(const Vect2d& vec2) {
        return Vect2d(this->x + vec2.x, this->y + vec2.y);
    }

	double x;
	double y;
};


}

#endif
