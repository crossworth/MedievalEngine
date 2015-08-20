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

    std::string tmpBitsPerPixel, tmpHeight, tmpWidth, tmpFullScreen, tmpWindowName, tmpIconName;

    tmpBitsPerPixel = mConfigurations.getKey("bits_per_pixel");
    tmpHeight       = mConfigurations.getKey("height");
    tmpWidth        = mConfigurations.getKey("width");
    tmpFullScreen   = mConfigurations.getKey("fullscreen");
    tmpWindowName   = mConfigurations.getKey("engine_name");
    tmpIconName     = mConfigurations.getKey("icon");

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

    if (tmpIconName != "") {
        mWindow.setIcon(tmpIconName);
    }

    mAssetsManager = AssetsManager::getInstance();

    mGUI = nullptr;
}

void MedievalEngine::init() {

    mGUI = new GUI(mWindow.getWindowInfo());

    mGameStateManager.add("loading", new LoadingScreen(this));
    mGameStateManager.setGameState("loading");

    LOG << Log::VERBOSE << "[MedievalEngine::init]" << std::endl;
}

void MedievalEngine::run() {
    while(mWindow.isOpen()) {

        Event event;
        while(mWindow.pollEvent(event)) {
            mGameStateManager.handleEvents(event);
            mGUI->handleEvents(event, mWindow);
        }

        mGameStateManager.update();
        mGUI->update();

        mWindow.clear();
        mGameStateManager.draw(mWindow);
        mGUI->draw(mWindow);
        mWindow.display();
    }
}

void MedievalEngine::close() {
    LOG << Log::VERBOSE << "[MedievalEngine::close]" << std::endl;
    mWindow.close();
}

Window* MedievalEngine::getWindow() {
    return &mWindow;
}

AssetsManager* MedievalEngine::getAssetsManager() {
    return mAssetsManager;
}

GameStateManager* MedievalEngine::getGameStateManager() {
    return &mGameStateManager;
}

GUI* MedievalEngine::getGUI() {
    return mGUI;
}

MedievalEngine::~MedievalEngine() {
    LOG << Log::VERBOSE << "[MedievalEngine::~MedievalEngine]" << std::endl;
    delete mAssetsManager;
}
