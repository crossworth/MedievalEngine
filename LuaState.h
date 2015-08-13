#ifndef MAINSTATE_H
#define MAINSTATE_H
#include "GameState.h"
#include "editor.h"

namespace ME {

class LuaState : public GameState {
public:
    LuaState(std::string name, std::string path);
    void init();
    void render();
    void handleEvents();
    void update();
    void play();
    void pause();
    void restart();
    void onEnableTransition();
    void onDisableTransition();
    ~LuaState();
private:
    std::string name;
    std::string path;
};

}

#endif // MAINSTATE_H
