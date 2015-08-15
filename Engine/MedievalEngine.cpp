#include "MedievalEngine.h"

using namespace ME;

MedievalEngine* MedievalEngine::mInstance = nullptr;

MedievalEngine* MedievalEngine::getInstance(int argc, char **argv) {
    if (!mInstance) {
        mInstance = new MedievalEngine(argc, argv);
    }
    return mInstance;
}

MedievalEngine::MedievalEngine(int argc, char** argv) : mAssetsManager(nullptr), mArguments(argc, argv) {

    if (mArguments.hasArgument("config")) {
        mConfigurations.readFile(mArguments.getArgument("config"));
    } else {
        mConfigurations.readFile(ENGINE_DEFAULTS::CONFIG_FILE);
    }

    WindowInfo mWindowInfo;

    std::string tmpBitsPerPixel, tmpHeight, tmpWidth, tmpFullScreen, tmpWindowName;

    tmpBitsPerPixel = mConfigurations.getKey("bits_per_pixel");
    tmpHeight       = mConfigurations.getKey("height");
    tmpWidth        = mConfigurations.getKey("width");
    tmpFullScreen   = mConfigurations.getKey("fullscreen");
    tmpWindowName   = mConfigurations.getKey("engine_name");

    if(tmpBitsPerPixel != "") {
        mWindowInfo.bitsPerPixel = Data2::str_to_int(tmpBitsPerPixel);
    }

    if(tmpHeight != "") {
        mWindowInfo.height = Data2::str_to_int(tmpHeight);
    }

    if(tmpWidth != "") {
        mWindowInfo.width = Data2::str_to_int(tmpWidth);
    }

    if(tmpFullScreen != "") {
        mWindowInfo.fullScreen = Data2::str_to_bool(tmpFullScreen);
    }

    if (tmpWindowName != "") {
        mWindowInfo.windowName = tmpWindowName;
    }

    mWindow.create(mWindowInfo);
    mAssetsManager = AssetsManager::getInstance();

}

void MedievalEngine::init() {
    // Where we start our game state and handle all the gamestate things

    MEid idMarioSptAn = mAssetsManager->createSpriteAnimation();
    marioSptAn = static_cast<SpriteAnimation*>(mAssetsManager->getAsset(idMarioSptAn));

    MEid idAn1 = mAssetsManager->loadTexture("/animation/1.png");
    MEid idAn2 = mAssetsManager->loadTexture("/animation/2.png");
    MEid idAn3 = mAssetsManager->loadTexture("/animation/3.png");
    MEid idAn4 = mAssetsManager->loadTexture("/animation/4.png");

    marioSptAn->addFrame(100, static_cast<Texture*>(mAssetsManager->getAsset(idAn1)));
    marioSptAn->addFrame(100, static_cast<Texture*>(mAssetsManager->getAsset(idAn2)));
    marioSptAn->addFrame(100, static_cast<Texture*>(mAssetsManager->getAsset(idAn3)));
    marioSptAn->addFrame(100, static_cast<Texture*>(mAssetsManager->getAsset(idAn4)));

    marioSptAn->setPosition(Vect2f((mWindow.getSize().x/2)-(marioSptAn->getSize().x/2), mWindow.getSize().y-marioSptAn->getSize().y));
    marioSptAn->setOriginCenter();

    MEid mTex = mAssetsManager->loadTexture("state/main/bg.jpg");
    MEid mSpr = mAssetsManager->createSprite(mTex);
    spriteObj = static_cast<Sprite*>(mAssetsManager->getAsset(mSpr));
    spriteObj->setSize(Vect2f(ENGINE_DEFAULTS::WIDTH_WINDOW, ENGINE_DEFAULTS::HEIGHT_WINDOW));

    MEid idFont = mAssetsManager->loadFont("font/YanoneKaffeesatz-Regular.ttf");
    MEid idText = mAssetsManager->createText("MedievalEngine", 76, idFont);

    textObj = static_cast<Text*>(mAssetsManager->getAsset(idText));
    textObj->setTextShadow(2.0f);
    textObj->setPosition(Vect2f((mWindow.getSize().x/2)-(textObj->getSize().x/2), 50.0f));


    MEid idMusic = mAssetsManager->loadMusic("music.ogg");
//    static_cast<Music*>(mAssetsManager->getAsset(idMusic))->play();

    idSound = mAssetsManager->loadMusic("sound.ogg");
}

void MedievalEngine::run() {
    while(mWindow.isOpen()) {
        sf::Event evt;
        while(mWindow.pollEvent(evt)){
            if(evt.type == sf::Event::Closed) {
                close();
            }
            if(evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::Space) {
                static_cast<Sound*>(mAssetsManager->getAsset(idSound))->play();
            }

            if(evt.key.code == sf::Keyboard::Right) {
                marioSptAn->move(Vect2f(5.f, 0.0f));
            }

            if(evt.key.code == sf::Keyboard::Left) {
                marioSptAn->move(Vect2f(-5.f, 0.0f));
            }

            if(evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::Up) {
               marioSptAn->setOpacity(marioSptAn->getOpacity() + 0.1f);
            }

            if(evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::Down) {
                marioSptAn->setOpacity(marioSptAn->getOpacity() - 0.1f);
            }
        }
        mWindow.clear();
        mWindow.draw(spriteObj);
        mWindow.draw(textObj);
        mWindow.draw(marioSptAn);

        marioSptAn->rotate(1.0f);

        mWindow.display();
    }
}

void MedievalEngine::close() {
    mWindow.close();
}

Window* MedievalEngine::getWindow() {
    return &mWindow;
}

AssetsManager* MedievalEngine::getAssetsManager() {
    return mAssetsManager;
}
