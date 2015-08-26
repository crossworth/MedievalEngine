#ifndef EFFECTS_H
#define EFFECTS_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Graphics/Drawable.h>


namespace ME {

class Drawable;

class Effects {
public:
    enum Type { FADE, STROBE, BLUR, BLOM };
public:
    Effects();
    virtual void update(Drawable* object) = 0;
    virtual bool done() = 0;
    Type getType();
    std::string getTypeStd();

    void resetClock();

    void setDone();
protected:
    Type m_type;
    sf::Clock mClock;
    bool m_done;
};


}
#endif // EFFECTS_H
