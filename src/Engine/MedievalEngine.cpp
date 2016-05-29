#include "MedievalEngine.h"

using namespace ME;

MedievalEngine::MedievalEngine(int argc, char** argv) : mArguments(argc, argv),
    mErrorCode(0), GAME_FONT_ID(0), mDoneLoading(false), mRunning(true) {

    ProfileBlock();

    LuaAPI::loadLibs();

    // We verify if a config argument has been passed, if so we load the engine
    // with the specified configuration file
    if (mArguments.hasArgument("config")) {
        mConfigurations.readFile(mArguments.getArgument("config"));
    } else {
        // Read the default configuration file
        if (!mConfigurations.readFile(ENGINE_DEFAULTS::CONFIG_FILE)) {

        }
    }

    // Since its the creation of our engine we create a temporary window object
    // to initialize our window

    std::string width;
    std::string height;
    std::string bitsPerPixel;
    std::string fullScreen;
    std::string windowName;
    std::string language;
    std::string globalVolume;
    std::string voiceVolume;
    std::string musicVolume;
    std::string ambientVolume;
    std::string vsync;
    std::string frameLimit;

    // Try the keys of the configuration file
    bitsPerPixel  = mConfigurations.getKey("bits_per_pixel");
    height        = mConfigurations.getKey("height");
    width         = mConfigurations.getKey("width");
    fullScreen    = mConfigurations.getKey("fullscreen");
    vsync         = mConfigurations.getKey("vsync");
    frameLimit    = mConfigurations.getKey("frame_limit");
    windowName    = mConfigurations.getKey("engine_name");
    language      = mConfigurations.getKey("language");
    globalVolume  = mConfigurations.getKey("global_volume");
    voiceVolume   = mConfigurations.getKey("voice_volume");
    musicVolume   = mConfigurations.getKey("music_volume");
    ambientVolume = mConfigurations.getKey("ambient_volume");


    // Verify each key to see if we do have a valid information if so we parse
    // to the correct type and put on the appropriate place
    if(bitsPerPixel != "") {
        mWindowInfoInput.bitsPerPixel = Kit::str_int(bitsPerPixel);
    }

    if(height != "") {
        mWindowInfoInput.height = Kit::str_int(height);
    }

    if(width != "") {
        mWindowInfoInput.width = Kit::str_int(width);
    }

    if(fullScreen != "") {
        mWindowInfoInput.fullScreen = Kit::str_bool(fullScreen);
    }

    if(vsync != "") {
        mWindowInfoInput.vsync = Kit::str_bool(vsync);
    }

    if(frameLimit != "") {
        mWindowInfoInput.frameLimit = Kit::str_int(frameLimit);
    }

    if (windowName != "") {
        mWindowInfoInput.windowName = windowName;
    }

    // Max volume 100.f
    if (globalVolume != "") {
        Audible::GLOBAL_VOLUME = std::min(Kit::str_float(globalVolume), 100.f);
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

    std::cout << "l: " << language << std::endl;

    mWindow.close();
    mErrorCode = 3;

    // Try to open the language file specified on the configuration file
    // If we failed to load the language file or its not informed on the configuration file
    // we try to load the default language file
    if (language == "" || !Strings::openLanguageFile(ENGINE_DEFAULTS::LANG_PATH + language)) {
        std::cout << ENGINE_DEFAULTS::LANG_PATH << " lang_path" << std::endl;
        std::cout << language << " << language" << std::endl;
        // If we failed to open the default language file we close the engine
        if (!Strings::openLanguageFile(ENGINE_DEFAULTS::LANG_PATH + ENGINE_DEFAULTS::LANGUAGE)) {
            LOG << Log::CRITICAL
                << "[MedievalEngine::MedievalEngine] Could not get the default language pack "
                << ENGINE_DEFAULTS::LANG_PATH + ENGINE_DEFAULTS::LANGUAGE
                << " neither the language specific "
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
    ProfileBlock();
   LOG << Log::VERBOSE << "[MedievalEngine::loadingThread]" << std::endl;
    // Here we register all our game states and call all the init create methods

    mGameStateManager.add("menu", new MenuScreen());
    mGameStateManager.getGameState("menu")->registerEngine(this);


    // Once we loaded all the gameStates and assets we set this mDoneLoading to true
    // to stop the loading screen
    mDoneLoading = true;
}

bool MedievalEngine::isLoadingThreadDone() {
    return mDoneLoading;
}

void MedievalEngine::init() {
    if (!isRunning()) {
        return;
    }

    ProfileBlock();
    LOG << Log::VERBOSE << "[MedievalEngine::init]" << std::endl;

    // Verify if we do have a game font key
    // if so we load it else we set to the fallback font
    // NOTE(Pedro): If the font its not load correctly it still get its ResourceID
    // and the font can be access to be load another font
    // A Log::WARNING should be emited
    if (mConfigurations.getKey("game_font") != "") {
        GAME_FONT_ID = mResourceManager.loadFont(mConfigurations.getKey("game_font"));
    } else {
        GAME_FONT_ID = Font::DEFAULT_FONT;
    }

    // We create the window here so We dont have any freeze on the screen
    mWindow.create(mWindowInfoInput);

    mGameStateManager.add("loading", new LoadingScreen());
    mGameStateManager.getGameState("loading")->registerEngine(this);
    mGameStateManager.setGameState("loading");

    // Open the window only after the loading screen has been initialized
    mWindow.open();


    // Register the engine on our console
    mConsole.registerEngine(this);


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
    mLoadingThread = std::thread(&MedievalEngine::loadingThread, this);

    // expose Lua functions
    LuaAPI::state.set_function("engine_close", &MedievalEngine::close, this);
    LuaFunctions::store("engine_close");

    LuaAPI::state.set_function("engine_is_running", &MedievalEngine::isRunning, this);
    LuaFunctions::store("engine_is_running");

    LuaAPI::state.set_function("engine_is_loading_thread_done", &MedievalEngine::isLoadingThreadDone, this);
    LuaFunctions::store("engine_is_loading_thread_done");
}

void MedievalEngine::run() {
    if (!isRunning()) {
       return;
    }


    ProfileBlock();
    while(mWindow.isOpen()) {
        ProfileBlockStr("Main game loop");

        { 
            ProfileBlockStr("update music queue");
            if (mMusicQueue.find(mCurrentMusicQueue) != mMusicQueue.end()) {
                // Update the current music queue
                // even if the music it's aready playing this should be called
                // to update the next music and verifiy if the current music status
                mMusicQueue[mCurrentMusicQueue].update();
            }
        }

        {
            ProfileBlockStr("poll events");
            Event event;
            while(mWindow.pollEvent(event)) {
                // We pass the handle events responsability
                // to the current game state, so this way
                // if the current game state it's doing something
                // critical it can decide what it should do.

                // If the console it's not visible we handle the game state events
                if (!mConsole.isVisible()) {
                    mGameStateManager.handleEvents(event);
                }

                // handle the console events, since it's independent
                mConsole.handleEvents(event);
            }
        }

        {
            ProfileBlockStr("update game state");
            mGameStateManager.update();
        }

        {
            ProfileBlockStr("window clear");
            mWindow.clear();
        }

        {
            ProfileBlockStr("draw game state");
            mGameStateManager.draw(mWindow);
        }

        if (mConsole.isVisible()) {
            mConsole.draw(mWindow);
        }

        if (Profiler::isVisible()) {
            Profiler::printRecords(this);
        }

        {
            ProfileBlockStr("window display");
            mWindow.display();
        }

        {
            ProfileBlockStr("window set title fps");
            // TODO(Pedro): remove this after, maybe make a flag
            mWindow.setTitle("FPS:" + Kit::int_str(mWindow.getFPS()));
        }
        
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
        mErrorCode = 0;

        // Close the window and wait for the thread to finish the loading
        // if we dont the engine crash horrible
        mLoadingThread.join();
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
