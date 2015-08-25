#include "MedievalEngine.h"

using namespace ME;

MedievalEngine::MedievalEngine(int argc, char** argv) : mArguments(argc, argv),
    mErroCode(0) {

    if (mArguments.hasArgument("config")) {
        mConfigurations.readFile(mArguments.getArgument("config"));
    } else {
        mConfigurations.readFile(ENGINE_DEFAULTS::CONFIG_FILE);
    }

    WindowInfo mWindowInfo;

    std::string tmpBitsPerPixel;
    std::string tmpHeight;
    std::string tmpWidth;
    std::string tmpFullScreen;
    std::string tmpWindowName;
    std::string tmpIconName;

    tmpBitsPerPixel = mConfigurations.getKey("bits_per_pixel");
    tmpHeight       = mConfigurations.getKey("height");
    tmpWidth        = mConfigurations.getKey("width");
    tmpFullScreen   = mConfigurations.getKey("fullscreen");
    tmpWindowName   = mConfigurations.getKey("engine_name");
    tmpIconName     = mConfigurations.getKey("icon");

    if(tmpBitsPerPixel != "") {
        mWindowInfo.bitsPerPixel = Kit::str_int(tmpBitsPerPixel);
    }

    if(tmpHeight != "") {
        mWindowInfo.height = Kit::str_int(tmpHeight);
    }

    if(tmpWidth != "") {
        mWindowInfo.width = Kit::str_int(tmpWidth);
    }

    if(tmpFullScreen != "") {
        mWindowInfo.fullScreen = Kit::str_bool(tmpFullScreen);
    }

    if (tmpWindowName != "") {
        mWindowInfo.windowName = tmpWindowName;
    }

    mWindow.create(mWindowInfo);

    if (tmpIconName != "") {
        mWindow.setIcon(tmpIconName);
    }

    if (!mDataFiles.openFile(ENGINE_DEFAULTS::DATA_PATH +
                             ENGINE_DEFAULTS::DEFAULT_DATFILE)) {
        LOG << Log::CRITICAL
            << "[MedievalEngine::MedievalEngine] Could not open the default assets file "
            << ENGINE_DEFAULTS::DEFAULT_DATFILE.c_str()
            << SM::FILE_EXTENSION.c_str() << std::endl;

        mWindow.close();
        mErroCode = 1;
    } else {
        if (mDataFiles.getName() == ENGINE_DEFAULTS::DATFILE_SIGNATURE_NAME &&
            mDataFiles.getVersion() == ENGINE_DEFAULTS::DATFILE_SIGNATURE_VERSION ) {
            Font::DEFAULT_FONT = mAssetsManager.loadFont(mDataFiles.getFile("default.ttf"),
                                                         mDataFiles.getFileEntrySize("default.ttf"));

            LOG << Log::VERBOSE
                << "[MedievalEngine::MedievalEngine] Default font loaded "
                << std::endl;
        } else {
            LOG << Log::CRITICAL << "[MedievalEngine::MedievalEngine] Default asset pack not recognized "
            << ENGINE_DEFAULTS::DEFAULT_DATFILE.c_str()
            << SM::FILE_EXTENSION.c_str() << std::endl;

            mWindow.close();
            mErroCode = 2;
        }
    }
}

void MedievalEngine::init() {
    if (!isRunning()) {
        return;
    }

    LOG << Log::VERBOSE << "[MedievalEngine::init]" << std::endl;
    mGUI.registerEngine(this);

    mGameStateManager.add("loading", new LoadingScreen(this));
    mGameStateManager.getGameState("loading")->registerEngine(this);
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
            mGUI.handleEvents(event, mWindow);
        }

        mGameStateManager.update();
        mGUI.update();

        mWindow.clear();
        mGameStateManager.draw(mWindow);
        mGUI.draw(mWindow);
        mWindow.display();
    }
}

int MedievalEngine::getErrorCode() {
    return mErroCode;
}

bool MedievalEngine::isRunning() {
    if (mErroCode == 0) {
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

ResourceManager* MedievalEngine::getAssetsManager() {
    return &mAssetsManager;
}

GameStateManager* MedievalEngine::getGameStateManager() {
    return &mGameStateManager;
}

GUI* MedievalEngine::getGUI() {
    return &mGUI;
}

SM::DATFile* MedievalEngine::getDATAFileHandle() {
    return &mDataFiles;
}

MedievalEngine::~MedievalEngine() {
    LOG << Log::VERBOSE << "[MedievalEngine::~MedievalEngine]" << std::endl;
}
