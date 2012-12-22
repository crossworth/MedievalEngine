#ifndef MAINSTATE_H
#define MAINSTATE_H
#include "gamestate.h"
#include "editor.h"

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
    void restart();
    ~mainState();
private:
};

}

#endif // MAINSTATE_H
