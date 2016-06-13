#include "LoadingScreen.h"
#include "Engine/MedievalEngine.h"

using namespace ME;

LoadingScreen::LoadingScreen() : fadeTextInit(false), mIsStateChanging(false) {
    LOG << Log::VERBOSE << "[LoadingScreen::LoadingScreen]" << std::endl;
}

void LoadingScreen::create() {
    ProfileBlock();
    LOG << Log::VERBOSE << "[LoadingScreen::create]" << std::endl;

    std::string textBackgroundName = "loading_screen_menu_bg_blur_png";

    ResourceManager::loadTexture(textBackgroundName, "menu/bg_blur.png");

    std::string sceneBackgroundName = "loading_screen_background_sprite";

    ResourceManager::createSprite(sceneBackgroundName, textBackgroundName);

    sceneBGPtr = ResourceManager::get<Sprite>(sceneBackgroundName);

    Vect2f windowSize = mEngine->getWindow()->getSize();

    Window::setSizeFullScreen(sceneBGPtr);


    std::string textMessageScreenName = "loading_screen_text_message";
    ResourceManager::createText(textMessageScreenName, Strings::getItemArrayRandom("loading_text"), Window::fontSize(0.4f), "game_font");
    
    std::string textLoadingScreenName = "loading_screen_loading_message";
    ResourceManager::createText(textLoadingScreenName, Strings::get("loading"), Window::fontSize(0.45f), "game_font");

    textMessageScreen = ResourceManager::get<Text>(textMessageScreenName);
    textLoadingScreen = ResourceManager::get<Text>(textLoadingScreenName);

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