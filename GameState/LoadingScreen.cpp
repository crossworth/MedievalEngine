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

    idBackground            = mAssets->createShape(winSize);
    Shape* mShapeBackground = mAssets->getAsset<Shape>(idBackground);

    mShapeBackground->setColor(Color::DODGER_BLUE);

    mEngine->getGUI()->addObject("engine_title", new TextObject(L"MedievalEngine", 72));
    mEngine->getGUI()->addObject("button_iniciar", new ButtonObject(L"Iniciar", Vect2f(mEngine->getWindow()->getSize().x - 150.f, mEngine->getWindow()->getSize().y - 200.f)));
    mEngine->getGUI()->addObject("button_opcoes", new ButtonObject(L"Opções", Vect2f(mEngine->getWindow()->getSize().x - 150.f, mEngine->getWindow()->getSize().y - 160.f)));
    mEngine->getGUI()->addObject("button_sair", new ButtonObject(L"Sair", Vect2f(mEngine->getWindow()->getSize().x - 150.f, mEngine->getWindow()->getSize().y - 120.f)));
    mEngine->getGUI()->addObject("debugger_info", new TextScrollListObject());

    mEngine->getGUI()->getObject<TextScrollListObject>("debugger_info")->addText(L"teste");
    mEngine->getGUI()->getObject<TextScrollListObject>("debugger_info")->addText(L"teste segunda linha");

}

void LoadingScreen::onEnable(Window &window) {
    setCurrentStatus(GAMESTATE_STATUS::ON_PLAYING);
}

void LoadingScreen::onDisable(Window &window) {

}

void LoadingScreen::onPlaying(Window &window) {
    window.draw(mEngine->getAssetsManager()->getAsset<Shape>(idBackground));
}

void LoadingScreen::update() {

}

void LoadingScreen::handleEvents(Event& evt) {
    if(evt.type == Event::Closed) {
        mEngine->getWindow()->close();
    }



    if (evt.type == Event::KeyPressed ) {

        if (evt.key.code == Keyboard::Space) {
            mEngine->getGUI()->getObject<TextScrollListObject>("debugger_info")->addText(L"teste outra linha");
        }

        if (evt.key.code == Keyboard::A) {
            mEngine->getGUI()->getObject<TextScrollListObject>("debugger_info")->setTextAutoScroll(true);
        }


    }
}



