#include "MedievalEngine.h"

using namespace ME;

MedievalEngine::MedievalEngine(int argc, char** argv) : mArguments(argc, argv),
    mErrorCode(0), gameFontID(0), mDoneLoading(false), mRunning(true) {

    // We verify if a config argument has been passed, if so We load the engine
    // with the specified configuration file
    if (mArguments.hasArgument("config")) {
        mConfigurations.readFile(mArguments.getArgument("config"));
    } else {
        // TODO(Pedro): if configuration file not found
        // do something
        mConfigurations.readFile(ENGINE_DEFAULTS::CONFIG_FILE);
    }

    // Since its the creation of our engine we create a temporary window object
    // to initialize our window
    mWindowInfo_;


    // TODO(Pedro): add the vsync and framelimit options
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

    // Try the keys of the configuration file
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


    // Verify each key to see if we do have a valid information if so we parse
    // to the correct type and put on the appropriate place
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

    // Max volume 100
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

    // Try to open the language file specified on the configuration file
    // If we failed to load the language file or its not informed on the configuration file
    // we try to load the default language file
    if (language == "" || !Strings::openLanguageFile(ENGINE_DEFAULTS::LANG_PATH + language)) {

        // If we failed to open the default language file we close the engine
        if (!Strings::openLanguageFile(ENGINE_DEFAULTS::LANG_PATH + ENGINE_DEFAULTS::LANGUAGE)) {
            LOG << Log::CRITICAL
                << "[MedievalEngine::MedievalEngine] Could not open the language pack "
                << language << std::endl;

            mWindow.close();
            mErrorCode = 3;
        }
    }


    // Try to open the default engine data file
    // If we cant open it we close the engine
    if (!mDataFiles.openFile(ENGINE_DEFAULTS::DATA_PATH +
                             ENGINE_DEFAULTS::DEFAULT_DATFILE)) {
        LOG << Log::CRITICAL
            << "[MedievalEngine::MedievalEngine] Could not open the default assets file "
            << ENGINE_DEFAULTS::DEFAULT_DATFILE.c_str() << std::endl;

        mWindow.close();
        mErrorCode = 1;
    } else {

        // If we can open the file but the signature its different we close the engine as well
        if (mDataFiles.getName() == ENGINE_DEFAULTS::DATFILE_SIGNATURE_NAME &&
            mDataFiles.getVersion() == ENGINE_DEFAULTS::DATFILE_SIGNATURE_VERSION ) {

            // Load the default engine font for the engine, its the fallback font for all the
            // string related stuff
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
* This is our loading thread
**/
void MedievalEngine::loadingThread() {
    LOG << Log::VERBOSE << "[MedievalEngine::loadingThread]" << std::endl;
    // Here we register all our game states and call all the init create methods

    mGameStateManager.add("menu", new MenuScreen());
    mGameStateManager.getGameState("menu")->registerEngine(this);


    // Once we loaded all the gameStates and assets we set this mDoneLoading to true
    // to stop the loading screen
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

    // Verify if we do have a game font key
    // if so we load it else we set to the fallback font
    // NOTE(Pedro): If the font its not load correctly it still get its ResourceID
    // and the font can be access to be load another font
    // A Log::WARNING should be emited
    if (mConfigurations.getKey("game_font") != "") {
        gameFontID = mResourceManager.loadFont(mConfigurations.getKey("game_font"));
    } else {
        gameFontID = Font::DEFAULT_FONT;
    }

    // We create the window here so We dont have any freeze on the screen
    mWindow.create(mWindowInfo_);


    mGameStateManager.add("loading", new LoadingScreen());
    mGameStateManager.getGameState("loading")->registerEngine(this);
    mGameStateManager.setGameState("loading");

    // Open the window only after the loading screen has been initialized
    mWindow.open();


    // Set an icon and cursor if we find it on the configuration file
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

        if (mMusicQueue.find(mCurrentMusicQueue) != mMusicQueue.end()) {
            // Update the current music queue
            // even if the music it's aready playing this should be called
            // to update the next music and verifiy if the current music status
            mMusicQueue[mCurrentMusicQueue].update();
        }

        Event event;
        while(mWindow.pollEvent(event)) {
            // We pass the handle events responsability
            // to the current game state, so this way
            // if the current game state it's doing something
            // critical it can decide what it should do.
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

void MedievalEngine::setCurrentMusicQueue(const std::string& name) {
    mCurrentMusicQueue = name;
}

MusicQueue* MedievalEngine::getMusicQueue(const std::string& name) {
    // If we dont find any music queue we just create one
    // and register our engine on it
    if (!(mMusicQueue.find(name) != mMusicQueue.end())) {
        LOG << Log::VERBOSE << "[MedievalEngine::getMusicQueue] "
            << "Muisc Queue " + name + " not found, creating new Music Queue" << std::endl;

        mMusicQueue[name] = MusicQueue();
        mMusicQueue[name].registerEngine(this);
    }

    return &mMusicQueue[name];
}

void MedievalEngine::close() {
    LOG << Log::VERBOSE << "[MedievalEngine::close]" << std::endl;
    if (mWindow.isOpen()) {
        mRunning = false;
        mWindow.close();

        // Close the window and wait for the thread to finish the loading
        // if we dont the engine crash horrible
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
