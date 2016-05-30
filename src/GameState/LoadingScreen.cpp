#include "LoadingScreen.h"
#include "Engine/MedievalEngine.h"

using namespace ME;

LoadingScreen::LoadingScreen() : fadeTextInit(false), mIsStateChanging(false) {
    LOG << Log::VERBOSE << "[LoadingScreen::LoadingScreen]" << std::endl;
}

ResourceID LoadingScreen::menuMusic;

void LoadingScreen::create() {
    ProfileBlock();
    LOG << Log::VERBOSE << "[LoadingScreen::create]" << std::endl;

    ResourceID txtBackground     = mResources->loadTexture("menu/bg_blur.png");
    ResourceID sceneBackgroundID = mResources->createSprite(txtBackground);

    sceneBGPtr = mResources->getResource<Sprite>(sceneBackgroundID);

    Vect2f windowSize = mEngine->getWindow()->getSize();

    Window::setSizeFullScreen(sceneBGPtr);


    ResourceID textMessageScreenID = mResources->createText(Strings::getItemArrayRandom("loading_text"), Window::fontSize(0.4f), mEngine->GAME_FONT_ID);
    // ResourceID textLoadingScreenID = mResources->createText(sf::String("Opções"), Window::fontSize(0.45f), mEngine->GAME_FONT_ID);
    ResourceID textLoadingScreenID = mResources->createText(Strings::get("loading"), Window::fontSize(0.45f), mEngine->GAME_FONT_ID);

    textMessageScreen = mResources->getResource<Text>(textMessageScreenID);
    textLoadingScreen = mResources->getResource<Text>(textLoadingScreenID);

    textMessageScreen->setOriginCenter();
    textLoadingScreen->setOriginCenter();

    textLoadingScreen->setStyle(Text::FontStyle::BOLD);

    textMessageScreen->setPosition(Vect2f(windowSize.x / 2, windowSize.y / 2));
    textLoadingScreen->setPosition(Vect2f(windowSize.x / 2, windowSize.y - (textLoadingScreen->getSize().y * 4)));



    mEngine->getMusicQueue("menu")->insert("menu/menu.ogg");

    mEngine->setCurrentMusicQueue("menu");
    mEngine->getMusicQueue("menu")->setLoopMode(true);
    mEngine->getMusicQueue("menu")->play();
}

void LoadingScreen::init() {
    LOG << Log::VERBOSE << "[LoadingScreen::init]" << std::endl;

    counter = 0;
}

void LoadingScreen::onEnable(Window& window) {
    setCurrentStatus(GameState::Status::ON_PLAYING);
    mClock.restart();
}

void LoadingScreen::onDisable(Window& window) {

}

void LoadingScreen::onPlaying(Window& window) {
    ProfileBlock();

    window.draw(sceneBGPtr);
    window.draw(textLoadingScreen);

    if (fadeTextInit) {
        window.draw(textMessageScreen);
    }
}

void LoadingScreen::update() {
    ProfileBlock();

    if (mClock.getMilliSeconds() > 100 && fadeTextInit == false) {
        fadeTextInit = true;
        textMessageScreen->addEffect(new Fade(500, Fade::Type::FADEIN));
    }

    if (mClock.getMilliSeconds() > 500) {
        counter++;

        if (counter > 3) {
            counter = 1;
        }

        std::string finalDots = "";

        for(int i = 1; i <= counter; i++) {
            finalDots = finalDots + ".";
        }

        textLoadingScreen->setString(Strings::get("loading"));
        mClock.restart();
    }

    unsigned int delayTime = 1500;

    if (mMinWaitTime.getMilliSeconds() > delayTime && mEngine->isLoadingThreadDone() && mIsStateChanging == false) {

        mIsStateChanging = true;

        unsigned int fadeTime = 1000;

        textLoadingScreen->addEffect(new Fade(fadeTime, Fade::Type::FADEOUT));
        textMessageScreen->addEffect(new Fade(fadeTime, Fade::Type::FADEOUT));

        sceneBGPtr->addEffect(new Fade(fadeTime, Fade::Type::FADEOUT, [this] (void) {
            // Can change the game state to the next one
            mEngine->getGameStateManager()->changeGameState("menu");
        }));
    }
}

void LoadingScreen::handleEvents(Event& evt) {
    ProfileBlock();

    if(evt.type == Event::Closed) {
        mEngine->close();
    }
}


LoadingScreen::~LoadingScreen() {

}