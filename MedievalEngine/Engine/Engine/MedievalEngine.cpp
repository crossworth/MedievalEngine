#include "MedievalEngine.h"

using namespace ME;

MedievalEngine::MedievalEngine(int argc, char** argv) : mArguments(argc, argv),
    mErrorCode(0) {

    if (mArguments.hasArgument("config")) {
        mConfigurations.readFile(mArguments.getArgument("config"));
    } else {
        mConfigurations.readFile(ENGINE_DEFAULTS::CONFIG_FILE);
    }

    WindowInfo windowInfo;

    std::string width;
    std::string height;
    std::string bitsPerPixel;
    std::string fullScreen;
    std::string windowName;
    std::string iconName;

    bitsPerPixel = mConfigurations.getKey("bits_per_pixel");
    height       = mConfigurations.getKey("height");
    width        = mConfigurations.getKey("width");
    fullScreen   = mConfigurations.getKey("fullscreen");
    windowName   = mConfigurations.getKey("engine_name");
    iconName     = mConfigurations.getKey("icon");

    if(bitsPerPixel != "") {
        windowInfo.bitsPerPixel = Kit::str_int(bitsPerPixel);
    }

    if(height != "") {
        windowInfo.height = Kit::str_int(height);
    }

    if(width != "") {
        windowInfo.width = Kit::str_int(width);
    }

    if(fullScreen != "") {
        windowInfo.fullScreen = Kit::str_bool(fullScreen);
    }

    if (windowName != "") {
        windowInfo.windowName = windowName;
    }

    mWindow.create(windowInfo);

    if (iconName != "") {
        iconName.erase(remove(iconName.begin(), iconName.end(), ' '), iconName.end());
        mWindow.setIcon(iconName);
    }

    if (!mDataFiles.openFile(ENGINE_DEFAULTS::DATA_PATH +
                             ENGINE_DEFAULTS::DEFAULT_DATFILE)) {
        LOG << Log::CRITICAL
            << "[MedievalEngine::MedievalEngine] Could not open the default assets file "
            << ENGINE_DEFAULTS::DEFAULT_DATFILE.c_str() << std::endl;

        mWindow.close();
        mErrorCode = 1;
    } else {
        if (mDataFiles.getName() == ENGINE_DEFAULTS::DATFILE_SIGNATURE_NAME &&
            mDataFiles.getVersion() == ENGINE_DEFAULTS::DATFILE_SIGNATURE_VERSION ) {
            Font::DEFAULT_FONT = mResourceManager.loadFont(mDataFiles.getFile("default.ttf"),
                                                         mDataFiles.getFileEntrySize("default.ttf"));

            LOG << Log::VERBOSE
                << "[MedievalEngine::MedievalEngine] Default font loaded "
                << std::endl;
        } else {
            LOG << Log::CRITICAL << "[MedievalEngine::MedievalEngine] Default asset pack not recognized "
            << ENGINE_DEFAULTS::DEFAULT_DATFILE.c_str() << std::endl;

            mWindow.close();
            mErrorCode = 2;
        }
    }
}

void MedievalEngine::init() {
    if (!isRunning()) {
        return;
    }

    gameFontID = mResourceManager.loadFont("menu/pentagrams.ttf");

    LOG << Log::VERBOSE << "[MedievalEngine::init]" << std::endl;

    mGameStateManager.add("loading", new LoadingScreen(this));
    mGameStateManager.add("menu", new MenuScreen(this));
    mGameStateManager.getGameState("loading")->registerEngine(this);
    mGameStateManager.getGameState("menu")->registerEngine(this);
    mGameStateManager.setGameState("loading");
}

void MedievalEngine::run() {
    if (!isRunning()) {
       return;
    }
    while(mWindow.isOpen()) {

        Event event;
        while(mWindow.pollEvent(event)) {
            mGameStateManager.handleEvents(event);
        }

        mGameStateManager.update();

        mWindow.clear();
        mGameStateManager.draw(mWindow);
        mWindow.display();
    }
}

int MedievalEngine::getErrorCode() {
    return mErrorCode;
}

bool MedievalEngine::isRunning() {
    if (mErrorCode == 0) {
        return true;
    } else {
        return false;
    }
}

void MedievalEngine::close() {
    LOG << Log::VERBOSE << "[MedievalEngine::close]" << std::endl;
    if (mWindow.isOpen()) {
        mWindow.close();
    }
}

Window* MedievalEngine::getWindow() {
    return &mWindow;
}

ResourceManager* MedievalEngine::getResourceManager() {
    return &mResourceManager;
}

GameStateManager* MedievalEngine::getGameStateManager() {
    return &mGameStateManager;
}

DATFile* MedievalEngine::getDATAFileHandle() {
    return &mDataFiles;
}

MedievalEngine::~MedievalEngine() {
    LOG << Log::VERBOSE << "[MedievalEngine::~MedievalEngine]" << std::endl;
}
