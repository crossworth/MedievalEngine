#include "MenuScreen.h"
#include "Engine/MedievalEngine.h"

using namespace ME;

MenuScreen::MenuScreen(MedievalEngine* engine) {
    mEngine = engine;
    LOG << Log::VERBOSE << "[MenuScreen::MenuScreen]" << std::endl;
}

void MenuScreen::init() {
    LOG << Log::VERBOSE << "[MenuScreen::init]" << std::endl;

    Vect2f winSize = mEngine->getWindow()->getSize();

    // TODO(pedro): normalize the name of the variables

    ResourceID txtBackground = mResources->loadTexture("menu/bg_menu.png");
    sceneBackgroundID = mResources->createSprite(txtBackground);


    ResourceID txtMenu = mResources->loadTexture("menu/bg_options.png");
    backgroundOptionsID = mResources->createSprite(txtMenu);

    ResourceID txtLogo = mResources->loadTexture("menu/title_menu.png");
    logoID = mResources->createSprite(txtLogo);

    optNewGameID = mResources->createText("New Game", 15, mEngine->gameFontID);
    optContinueID = mResources->createText("Continue", 15, mEngine->gameFontID);
    optMultiplayerID = mResources->createText("Multiplayer", 15, mEngine->gameFontID);
    optOptionsID = mResources->createText("Options", 15, mEngine->gameFontID);
    optExitID = mResources->createText("Exit", 15, mEngine->gameFontID);



    Sprite* bgSprite = mResources->getResource<Sprite>(sceneBackgroundID);
    
    Vect2f ratio(0.f, 0.f);

    ratio.x =  winSize.x / bgSprite->getSize().x; 
    ratio.y =  winSize.y / bgSprite->getSize().y; 

    bgSprite->setSize(winSize);

    Sprite* bgMenuSprite = mResources->getResource<Sprite>(backgroundOptionsID);
    bgMenuSprite->setOriginCenter();

    Vect2f bgMenuSize = bgMenuSprite->getSize();

    bgMenuSprite->setSize(Vect2f(bgMenuSize.x * ratio.x, bgMenuSize.y * ratio.y));
    bgMenuSprite->setPosition(Vect2f(winSize.x - ( bgMenuSprite->getSize().x / 2 ), winSize.y / 2 ));



    // TODO(pedro): Set the text positions, BUT USE GUI Objects!


}

void MenuScreen::onEnable(Window &window) {
    setCurrentStatus(GAME_STATUS::ON_PLAYING);

    mResources->getResource<Sprite>(sceneBackgroundID)->addEffect(new Fade(1000, Fade::Type::FADEIN));
    mResources->getResource<Sprite>(backgroundOptionsID)->addEffect(new Fade(1000, Fade::Type::FADEIN));
}

void MenuScreen::onDisable(Window &window) {

}

void MenuScreen::onPlaying(Window &window) {
    window.draw(mResources->getResource<Sprite>(sceneBackgroundID));
    window.draw(mResources->getResource<Sprite>(backgroundOptionsID));
}

void MenuScreen::update() {

}

void MenuScreen::handleEvents(Event& evt) {
    if(evt.type == Event::Closed) {
        mEngine->getWindow()->close();
    }
}
