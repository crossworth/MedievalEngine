#ifndef MAINSTATE_H
#define MAINSTATE_H
#include "gamestate.h"
#include "editor.h"

namespace ME {

class luaState : public gameState {
public:
    luaState(std::string name, std::string path);
    void init();
    void render();
    void handleEvents();
    void update();
    void play();
    void pause();
    void restart();
    void onEnableTransition();
    void onDisableTransition();
    ~luaState();
private:
    std::string name;
    std::string path;
};

}

#endif // MAINSTATE_H
