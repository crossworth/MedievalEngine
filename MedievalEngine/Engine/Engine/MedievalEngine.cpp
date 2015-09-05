#include "MedievalEngine.h"

using namespace ME;

MedievalEngine::MedievalEngine(int argc, char** argv) : mArguments(argc, argv),
    mErrorCode(0), gameFontID(0), mDoneLoading(false), mRunning(true) {

    if (mArguments.hasArgument("config")) {
        mConfigurations.readFile(mArguments.getArgument("config"));
    } else {
        mConfigurations.readFile(ENGINE_DEFAULTS::CONFIG_FILE);
    }

     mWindowInfo_;

    std::string width;
    std::string height;
    std::string bitsPerPixel;
    std::string fullScreen;
    std::string windowName;
    std::string language;
    std::string volume;
    std::string voiceVolume;
    std::string musicVolume;
    std::string ambientVolume;

    bitsPerPixel  = mConfigurations.getKey("bits_per_pixel");
    height        = mConfigurations.getKey("height");
    width         = mConfigurations.getKey("width");
    fullScreen    = mConfigurations.getKey("fullscreen");
    windowName    = mConfigurations.getKey("engine_name");
    language      = mConfigurations.getKey("language");
    volume        = mConfigurations.getKey("volume");
    voiceVolume   = mConfigurations.getKey("voice_volume");
    musicVolume   = mConfigurations.getKey("music_volume");
    ambientVolume = mConfigurations.getKey("ambient_volume");

    if(bitsPerPixel != "") {
        mWindowInfo_.bitsPerPixel = Kit::str_int(bitsPerPixel);
    }

    if(height != "") {
        mWindowInfo_.height = Kit::str_int(height);
    }

    if(width != "") {
        mWindowInfo_.width = Kit::str_int(width);
    }

    if(fullScreen != "") {
        mWindowInfo_.fullScreen = Kit::str_bool(fullScreen);
    }

    if (windowName != "") {
        mWindowInfo_.windowName = windowName;
    }

    if (language == "") {
        language = ENGINE_DEFAULTS::LANGUAGE;
    }

    if (volume != "") {
        Audible::VOLUME = std::min(Kit::str_float(volume), 100.f);
    }

    if (voiceVolume != "") {
        Audible::VOICE_VOLUME = std::min(Kit::str_float(voiceVolume), 100.f);
    }

    if (musicVolume != "") {
        Audible::MUSIC_VOLUME = std::min(Kit::str_float(musicVolume), 100.f);
    }

    if (ambientVolume != "") {
        Audible::AMBIENT_VOLUME = std::min(Kit::str_float(ambientVolume), 100.f);
    }

    if (!Strings::openLanguageFile(ENGINE_DEFAULTS::LANG_PATH + language)) {
        if (!Strings::openLanguageFile(ENGINE_DEFAULTS::LANG_PATH + ENGINE_DEFAULTS::LANGUAGE)) {
            LOG << Log::CRITICAL
                << "[MedievalEngine::MedievalEngine] Could not open the language pack "
                << language << std::endl;

            mWindow.close();
            mErrorCode = 3;
        }
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


/**
* We call this from a Thread
**/
void MedievalEngine::loadingThread() {
    LOG << Log::VERBOSE << "[MedievalEngine::loadingThread]" << std::endl;
    // Here we register all our game states and call all the init create methods

    mGameStateManager.add("menu", new MenuScreen(this));
    mGameStateManager.getGameState("menu")->registerEngine(this);

    mDoneLoading = true;
}

bool MedievalEngine::doneLoading() {
    return mDoneLoading;
}

void MedievalEngine::init() {
    if (!isRunning()) {
        return;
    }

    LOG << Log::VERBOSE << "[MedievalEngine::init]" << std::endl;

    if (mConfigurations.getKey("game_font") != "") {
        gameFontID = mResourceManager.loadFont(mConfigurations.getKey("game_font"));
    } else {
        gameFontID = Font::DEFAULT_FONT;
    }

    // We create the window here so We dont have any freeze on the screen
    mWindow.create(mWindowInfo_);


    mGameStateManager.add("loading", new LoadingScreen(this));
    mGameStateManager.getGameState("loading")->registerEngine(this);
    mGameStateManager.setGameState("loading");

    mWindow.open();

    std::string iconName;
    std::string cursorName;
    iconName   = mConfigurations.getKey("icon");
    cursorName = mConfigurations.getKey("cursor");

    if (iconName != "") {
        mWindow.setIcon(iconName);
    }

    if (cursorName != "") {
        mWindow.setCursor(cursorName);
    }

    // Initilize our loading thread
    mLoadingThread = new std::thread(&MedievalEngine::loadingThread, this);
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
    return mRunning;
}

void MedievalEngine::close() {
    LOG << Log::VERBOSE << "[MedievalEngine::close]" << std::endl;
    // We dont close if We are in the loading Thread
    if (mWindow.isOpen()) {
        mRunning = false;
        mWindow.close();
        mLoadingThread->join();
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
    delete mLoadingThread;
}
