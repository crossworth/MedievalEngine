#ifndef EFFECTS_H
#define EFFECTS_H
#include "Config.h"

namespace ME {

class Effects {
public:
    Effects();
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual bool done() = 0;
    virtual std::string getSpriteName();
    virtual std::string getEffectName();
    virtual ~Effects();
protected:
    std::string mEffectName;
    std::string mSpriteName;
    sf::Clock mClock;
    bool mDone;
};


}
#endif // EFFECTS_H
