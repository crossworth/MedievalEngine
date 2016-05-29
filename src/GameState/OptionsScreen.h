#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H
#include "GameState/GameState.h"


namespace ME {

class OptionsScreen : public GameState {
public:
    OptionsScreen();
    void init();
    void create();
    void onEnable(Window& window);
    void onDisable(Window& window);
    void onPlaying(Window& window);
    void update();
    void handleEvents(Event& evt);
    ~OptionsScreen();
private:



};

}

#endif // OPTIONSSCREEN_H