#include "MenuScreen.h"
#include "Engine/MedievalEngine.h"

using namespace ME;

MenuScreen::MenuScreen(MedievalEngine* engine) {
    mEngine = engine;
    LOG << Log::VERBOSE << "[MenuScreen::MenuScreen]" << std::endl;
}

void MenuScreen::init() {
    LOG << Log::VERBOSE << "[MenuScreen::init]" << std::endl;


    ResourceID txtBackground = mResources->loadTexture("menu/bg_menu.png");
    sceneBackgroundID = mResources->createSprite(txtBackground);
}

void MenuScreen::onEnable(Window &window) {
    setCurrentStatus(GAME_STATUS::ON_PLAYING);

    mResources->getResource<Sprite>(sceneBackgroundID)->addEffect(new Fade(5000, Fade::Type::FADEIN));
}

void MenuScreen::onDisable(Window &window) {

}

void MenuScreen::onPlaying(Window &window) {
    window.draw(mResources->getResource<Sprite>(sceneBackgroundID));
}

void MenuScreen::update() {

}

void MenuScreen::handleEvents(Event& evt) {
    if(evt.type == Event::Closed) {
        mEngine->getWindow()->close();
    }
}
