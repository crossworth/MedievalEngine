#ifndef EFFECTS_H
#define EFFECTS_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Graphics/Drawable.h>


namespace ME {

class Drawable;

class Effects {
public:
    Effects();
    virtual void update(Drawable* object) = 0;
    virtual bool done() = 0;
    std::string getType();

    void resetClock();

    void setDone();
protected:
    std::string mType;
    sf::Clock mClock;
    bool mDone;
};


}
#endif // EFFECTS_H
