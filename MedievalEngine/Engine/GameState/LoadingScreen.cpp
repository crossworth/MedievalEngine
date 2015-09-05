#include "LoadingScreen.h"
#include "Engine/MedievalEngine.h"

using namespace ME;

LoadingScreen::LoadingScreen(MedievalEngine* engine) : fadeTextInit(false), isChangeState(false) {
    mEngine = engine;
    LOG << Log::VERBOSE << "[LoadingScreen::LoadingScreen]" << std::endl;
}

void LoadingScreen::create() {
    LOG << Log::VERBOSE << "[LoadingScreen::create]" << std::endl;

    ResourceID txtBackground = mResources->loadTexture("menu/bg_blur.png");
    sceneBackgroundID = mResources->createSprite(txtBackground);

    Sprite* sceneBGPtr = mResources->getResource<Sprite>(sceneBackgroundID);

    Vect2f windowSize = mEngine->getWindow()->getSize();

    Window::fullScreen(sceneBGPtr);

    textMessageScreen = mResources->createText(Strings::get("loading_text"), Window::fontSize(0.4f), mEngine->gameFontID);
    textLoadingScreen = mResources->createText(Strings::get("loading"), Window::fontSize(0.45f), mEngine->gameFontID);

    Text* textMessageScreenPtr = mResources->getResource<Text>(textMessageScreen);
    Text* textLoadingScreenPtr = mResources->getResource<Text>(textLoadingScreen);

    textMessageScreenPtr->setOriginCenter();
    textLoadingScreenPtr->setOriginCenter();

    textLoadingScreenPtr->setStyle(Text::FontStyle::BOLD);

    textMessageScreenPtr->setPosition(Vect2f(windowSize.x / 2, windowSize.y / 2));
    textLoadingScreenPtr->setPosition(Vect2f(windowSize.x / 2, windowSize.y - (textLoadingScreenPtr->getSize().y * 4)));


    ResourceID musicBG = mResources->loadMusic("menu/menu.ogg");
    Music* music       = mResources->getResource<Music>(musicBG);
    music->setLoopMode(true);
    music->play();
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
    if (mClock.getTime() > 500 && fadeTextInit == false) {
        fadeTextInit = true;
        mResources->getResource<Text>(textMessageScreen)->addEffect(new Fade(1000, Fade::Type::FADEIN));
    }

    if (mClock.getTime() > 500) {
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

    unsigned int delayTime = 1000;

    if (mFakeLoadingTime.getTime() > delayTime && mEngine->doneLoading() && isChangeState == false) {
        isChangeState = true;

        unsigned int fadeTime = 500;

        mResources->getResource<Text>(textLoadingScreen)->addEffect(new Fade(fadeTime, Fade::Type::FADEOUT));
        mResources->getResource<Text>(textMessageScreen)->addEffect(new Fade(fadeTime, Fade::Type::FADEOUT));

        mResources->getResource<Text>(sceneBackgroundID)->addEffect(new Fade(fadeTime, Fade::Type::FADEOUT, [this] (void) {
            this->mEngine->getGameStateManager()->changeGameState("menu");
        }));
    }
}

void LoadingScreen::handleEvents(Event& evt) {
    if(evt.type == Event::Closed) {
        mEngine->close();
    }
}
