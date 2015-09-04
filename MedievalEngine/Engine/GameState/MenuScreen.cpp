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

    Sprite* logoSprite = mResources->getResource<Sprite>(logoID);
    Sprite* bgSprite = mResources->getResource<Sprite>(sceneBackgroundID);

    Vect2f ratio(0.f, 0.f);

    ratio.x =  winSize.x / bgSprite->getSize().x;
    ratio.y =  winSize.y / bgSprite->getSize().y;

    bgSprite->setSize(winSize);

    Sprite* bgMenuSprite = mResources->getResource<Sprite>(backgroundOptionsID);
    bgMenuSprite->setOriginCenter();
    logoSprite->setOriginCenter();

    Vect2f bgMenuSize = bgMenuSprite->getSize();

    bgMenuSprite->setSize(Vect2f(bgMenuSize.x * ratio.x, bgMenuSize.y * ratio.y));
    bgMenuSprite->setPosition(Vect2f(winSize.x - ( bgMenuSprite->getSize().x / 2 ), winSize.y / 2 ));

    Vect2f logoSize = logoSprite->getSize();
    logoSprite->setSize(Vect2f(logoSize.x * ratio.x, logoSize.y * ratio.y));


    Vect2f logoPosition(bgMenuSprite->getPosition());
    logoPosition.y = bgMenuSprite->getSize().y * 0.35f;

    logoSprite->setPosition(logoPosition);


    logoPosition.x = logoPosition.x - bgMenuSprite->getSize().x / 4;

    float paddingVerticalText = 40.f;

    logoPosition.y = logoPosition.y + paddingVerticalText;
    mGUI.addWidget("new_game_btn", TextWidgetPtr(new TextWidget("New Game", 35, logoPosition, mEngine->gameFontID)));
    mNewGame = mGUI.getWidget<TextWidget>("new_game_btn");

    logoPosition.y = logoPosition.y + paddingVerticalText;
    mGUI.addWidget("continue_bt", TextWidgetPtr(new TextWidget("Continue", 35, logoPosition, mEngine->gameFontID)));
    mContinue = mGUI.getWidget<TextWidget>("continue_bt");

    logoPosition.y = logoPosition.y + paddingVerticalText;
    mGUI.addWidget("multiplayer_btn", TextWidgetPtr(new TextWidget("Multiplayer", 35, logoPosition, mEngine->gameFontID)));
    mMultiplayer = mGUI.getWidget<TextWidget>("multiplayer_btn");

    logoPosition.y = logoPosition.y + paddingVerticalText;
    mGUI.addWidget("options_btn", TextWidgetPtr(new TextWidget("Options", 35, logoPosition, mEngine->gameFontID)));
    mOptions = mGUI.getWidget<TextWidget>("options_btn");

    logoPosition.y = logoPosition.y + paddingVerticalText;
    mGUI.addWidget("exit_btn", TextWidgetPtr(new TextWidget("Exit", 35, logoPosition, mEngine->gameFontID)));
    mExit = mGUI.getWidget<TextWidget>("exit_btn");


    mNewGame->setColor(Color::BLACK);
    mContinue->setColor(Color::BLACK);
    mMultiplayer->setColor(Color::BLACK);
    mOptions->setColor(Color::BLACK);
    mExit->setColor(Color::BLACK);


    // TODO(pedro): Set the text positions, BUT USE GUI Objects!
    mFadeTime = 1000;

    mResources->getResource<Sprite>(sceneBackgroundID)->addEffect(new Fade(mFadeTime, Fade::Type::FADEIN));
    mResources->getResource<Sprite>(logoID)->addEffect(new Fade(mFadeTime, Fade::Type::FADEIN));
    mGUI.addEffect(new Fade(mFadeTime, Fade::Type::FADEIN));
    mResources->getResource<Sprite>(backgroundOptionsID)->addEffect(new Fade(mFadeTime, Fade::Type::FADEIN, [this] (void) {
        this->setCurrentStatus(GAME_STATUS::ON_PLAYING);
    }));
}

void MenuScreen::onEnable(Window &window) {
    window.draw(mResources->getResource<Sprite>(sceneBackgroundID));
    window.draw(mResources->getResource<Sprite>(backgroundOptionsID));
    window.draw(mResources->getResource<Sprite>(logoID));
    window.draw(&mGUI);
}

void MenuScreen::onDisable(Window &window) {

}

void MenuScreen::onPlaying(Window &window) {
    window.draw(mResources->getResource<Sprite>(sceneBackgroundID));
    window.draw(mResources->getResource<Sprite>(backgroundOptionsID));
    window.draw(mResources->getResource<Sprite>(logoID));
    window.draw(&mGUI);
}

void MenuScreen::update() {
    mGUI.update();
}

void MenuScreen::handleEvents(Event& evt) {
    if(evt.type == Event::Closed) {
        mEngine->getWindow()->close();
    }
    mGUI.handleEvents(evt);
}


MenuScreen::~MenuScreen() {
    // TODO(pedro): See if this work's, since We are adding to the GUI object
    // maybe We must release from the GUI Object... or maybe it's a shared_ptr

}
