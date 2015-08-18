#include "LoadingScreen.h"
#include "MedievalEngine.h"

using namespace ME;

LoadingScreen::LoadingScreen(MedievalEngine* engine) {
    mEngine = engine;
}

void LoadingScreen::init() {

}

void LoadingScreen::onEnable(Window &window) {

}

void LoadingScreen::onDisable(Window &window) {

}

void LoadingScreen::onPlaying(Window &window) {

}

void LoadingScreen::update() {

}

void LoadingScreen::handleEvents(Event &evt) {
    if(evt.type == Event::Closed) {
        mEngine->getWindow()->close();
    }
}



