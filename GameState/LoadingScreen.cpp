#include "LoadingScreen.h"
#include "Engine/MedievalEngine.h"

using namespace ME;

LoadingScreen::LoadingScreen(MedievalEngine* engine) {
    mEngine = engine;
    LOG << Log::VERBOSE << "[LoadingScreen::LoadingScreen]" << std::endl;
}

void LoadingScreen::init() {
    LOG << Log::VERBOSE << "[LoadingScreen::init]" << std::endl;

    Vect2i winSize         = mEngine->getWindow()->getSize();
    AssetsManager* mAssets = mEngine->getAssetsManager();

    idBackground = mAssets->createShape(Vect2f(winSize));

    Shape* mShapeBackground = mAssets->getAsset<Shape>(idBackground);
    mShapeBackground->setColor(ColorGradient(Color::WHITE, Color::BUTTON_C3));

    MEid logoTxt = mAssets->loadTexture("logo.png");
    idLogo       = mAssets->createSprite(logoTxt);

    Sprite* spriteLogo = mAssets->getAsset<Sprite>(idLogo);
    spriteLogo->setOriginCenter();
    spriteLogo->setPosition(Vect2f(winSize.x/2, winSize.y/2));
    spriteLogo->setScale(Vect2f(winSize.x/(spriteLogo->getSize().x*2), winSize.y/(spriteLogo->getSize().y*2)));

    const int fadeInTime = 3;

    mAssets->getAsset<Shape>(idBackground)->addEffect(new Fade(fadeInTime, FADEIN));
    spriteLogo->addEffect(new Fade(fadeInTime, FADEIN));

//    static_cast<Music*>(mAssets->getAsset(mAssets->loadMusic("music.ogg")))->play();


    mEngine->getGUI()->addObject(new TextObject(L"Title", 32));
    mEngine->getGUI()->addObject(new ButtonObject(L"Iniciar", Vect2f(mEngine->getWindow()->getSize().x - 150.f, mEngine->getWindow()->getSize().y - 200.f)));
    mEngine->getGUI()->addObject(new ButtonObject(L"Opções", Vect2f(mEngine->getWindow()->getSize().x - 150.f, mEngine->getWindow()->getSize().y - 160.f)));
    mEngine->getGUI()->addObject(new ButtonObject(L"Sair", Vect2f(mEngine->getWindow()->getSize().x - 150.f, mEngine->getWindow()->getSize().y - 120.f)));
}

void LoadingScreen::onEnable(Window &window) {
    setCurrentStatus(GAMESTATE_STATUS::ON_PLAYING);
}

void LoadingScreen::onDisable(Window &window) {

}

void LoadingScreen::onPlaying(Window &window) {
    window.draw(mEngine->getAssetsManager()->getAsset<Shape>(idBackground));
    window.draw(mEngine->getAssetsManager()->getAsset<Sprite>(idLogo));
}

void LoadingScreen::update() {

}

void LoadingScreen::handleEvents(Event &evt) {
    if(evt.type == Event::Closed) {
        mEngine->getWindow()->close();
    }
}



