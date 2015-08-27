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
    ResourceManager* mAssets = mEngine->getResourceManager();


    spriteMario                 = mAssets->createSpriteAnimation();
    SpriteAnimation* marioSptAn = mAssets->getResource<SpriteAnimation>(spriteMario);

    ResourceID idAn1 = mAssets->loadTexture("/animation/1.png");
    ResourceID idAn2 = mAssets->loadTexture("/animation/2.png");
    ResourceID idAn3 = mAssets->loadTexture("/animation/3.png");
    ResourceID idAn4 = mAssets->loadTexture("/animation/4.png");

    marioSptAn->addFrame(100, mAssets->getResource<Texture>(idAn1));
    marioSptAn->addFrame(100, mAssets->getResource<Texture>(idAn2));
    marioSptAn->addFrame(100, mAssets->getResource<Texture>(idAn3));
    marioSptAn->addFrame(100, mAssets->getResource<Texture>(idAn4));

    marioSptAn->setPosition(Vect2f((winSize.x/2)-(marioSptAn->getSize().x/2),
    winSize.y-marioSptAn->getSize().y));


    idBackground            = mAssets->createShape(winSize);
    Shape* mShapeBackground = mAssets->getResource<Shape>(idBackground);

    mShapeBackground->setColor(Color::DODGER_BLUE);

    mEngine->getGUI()->addObject("engine_title", new TextObject(L"MedievalEngine", 72));
    mEngine->getGUI()->addObject("button_iniciar", new ButtonObject(L"Iniciar", Vect2f(mEngine->getWindow()->getSize().x - 150.f, mEngine->getWindow()->getSize().y - 200.f)));
    mEngine->getGUI()->addObject("button_opcoes", new ButtonObject(L"Opções", Vect2f(mEngine->getWindow()->getSize().x - 150.f, mEngine->getWindow()->getSize().y - 160.f)));
    mEngine->getGUI()->addObject("button_sair", new ButtonObject(L"Sair", Vect2f(mEngine->getWindow()->getSize().x - 150.f, mEngine->getWindow()->getSize().y - 120.f)));
    mEngine->getGUI()->addObject("debugger_info", new TextScrollListObject());

    mEngine->getGUI()->getObject<TextScrollListObject>("debugger_info")->addText(L"teste");
    mEngine->getGUI()->getObject<TextScrollListObject>("debugger_info")->addText(L"teste segunda linha");

    c = 0;
}

void LoadingScreen::onEnable(Window &window) {
    setCurrentStatus(GAME_STATUS::ON_PLAYING);
}

void LoadingScreen::onDisable(Window &window) {

}

void LoadingScreen::onPlaying(Window &window) {
    window.draw(mEngine->getResourceManager()->getResource<Shape>(idBackground));
    window.draw(mEngine->getResourceManager()->getResource<SpriteAnimation>(spriteMario));
}

void LoadingScreen::update() {

}

void LoadingScreen::handleEvents(Event& evt) {
    if(evt.type == Event::Closed) {
        mEngine->getWindow()->close();
    }

    if (evt.type == Event::KeyPressed ) {

        if (evt.key.code == Keyboard::Space) {
            std::string tmp("teste outra linha" + Kit::int_str(c++));
            mEngine->getGUI()->getObject<TextScrollListObject>("debugger_info")->addText(Kit::str_wstr(tmp));
        }

        if (evt.key.code == Keyboard::A) {
            mEngine->getGUI()->getObject<TextScrollListObject>("debugger_info")->setTextAutoScroll(true);
        }


        if (evt.key.code == Keyboard::F) {
            mEngine->getResourceManager()->getResource<Shape>(spriteMario)->addEffect(new Fade(5000, Fade::FADEIN, [](void){
                std::cout << " Shit just got real" << std::endl;
             }));

        }

        if (evt.key.code == Keyboard::D) {
            mEngine->getResourceManager()->getResource<Shape>(spriteMario)->addEffect(new Strobe(500, 0.9));
        }


    }
}



