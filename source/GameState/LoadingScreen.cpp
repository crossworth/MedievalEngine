#include "LoadingScreen.h"
#include "Engine/MedievalEngine.h"

using namespace ME;

LoadingScreen::LoadingScreen() : fadeTextInit(false), mIsStateChanging(false) {
    LOG << Log::VERBOSE << "[LoadingScreen::LoadingScreen]" << std::endl;
}

ResourceID LoadingScreen::menuMusic;

void LoadingScreen::create() {
    LOG << Log::VERBOSE << "[LoadingScreen::create]" << std::endl;

    ResourceID txtBackground = mResources->loadTexture("menu/bg_blur.png");
    sceneBackgroundID = mResources->createSprite(txtBackground);

    Sprite* sceneBGPtr = mResources->getResource<Sprite>(sceneBackgroundID);

    Vect2f windowSize = mEngine->getWindow()->getSize();

    Window::setSizeFullScreen(sceneBGPtr);


    textMessageScreen = mResources->createText(Strings::getItemArrayRandom("loading_text"), Window::fontSize(0.4f), mEngine->GAME_FONT_ID);
    textLoadingScreen = mResources->createText(Strings::get("loading"), Window::fontSize(0.45f), mEngine->GAME_FONT_ID);

    Text* textMessageScreenPtr = mResources->getResource<Text>(textMessageScreen);
    Text* textLoadingScreenPtr = mResources->getResource<Text>(textLoadingScreen);

    textMessageScreenPtr->setOriginCenter();
    textLoadingScreenPtr->setOriginCenter();

    textLoadingScreenPtr->setStyle(Text::FontStyle::BOLD);

    textMessageScreenPtr->setPosition(Vect2f(windowSize.x / 2, windowSize.y / 2));
    textLoadingScreenPtr->setPosition(Vect2f(windowSize.x / 2, windowSize.y - (textLoadingScreenPtr->getSize().y * 4)));



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
    window.draw(mResources->getResource<Sprite>(sceneBackgroundID));
    window.draw(mResources->getResource<Sprite>(textLoadingScreen));

    if (fadeTextInit) {
        window.draw(mResources->getResource<Text>(textMessageScreen));
    }
}

void LoadingScreen::update() {
    if (mClock.getMilliSeconds() > 100 && fadeTextInit == false) {
        fadeTextInit = true;
        mResources->getResource<Text>(textMessageScreen)->addEffect(new Fade(500, Fade::Type::FADEIN));
    }

    if (mClock.getMilliSeconds() > 500) {
        counter++;

        if (counter > 3) {
            counter = 1;
        }

        Text* textPtr = mResources->getResource<Text>(textLoadingScreen);

        std::string finalDots = "";

        for(int i = 1; i <= counter; i++) {
            finalDots = finalDots + ".";
        }

        textPtr->setString(Strings::get("loading") + finalDots);
        mClock.restart();
    }

    unsigned int delayTime = 1500;

    if (mMinWaitTime.getMilliSeconds() > delayTime && mEngine->isLoadingThreadDone() && mIsStateChanging == false) {
        mIsStateChanging = true;

        unsigned int fadeTime = 1000;

        mResources->getResource<Text>(textLoadingScreen)->addEffect(new Fade(fadeTime, Fade::Type::FADEOUT));
        mResources->getResource<Text>(textMessageScreen)->addEffect(new Fade(fadeTime, Fade::Type::FADEOUT));

        mResources->getResource<Text>(sceneBackgroundID)->addEffect(new Fade(fadeTime, Fade::Type::FADEOUT, [this] (void) {
            // Can change the game state to the next one
            this->mEngine->getGameStateManager()->changeGameState("menu");
        }));
    }
}

void LoadingScreen::handleEvents(Event& evt) {
    if(evt.type == Event::Closed) {
        mEngine->close();
    }
}
