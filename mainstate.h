#ifndef MAINSTATE_H
#define MAINSTATE_H
#include "gamestate.h"

namespace ME{

class mainState : public gameState
{
public:
    mainState();
    void init();
    void render();
    void handleEvents();
    void update();
    void play();
    void pause();
    ~mainState();
};

}

#endif // MAINSTATE_H
