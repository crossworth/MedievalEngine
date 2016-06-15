#include "MedievalEngine.h"

using namespace ME;

MedievalEngine::MedievalEngine(int argc, char **argv) : mArguments(argc, argv) {
    mDoneLoading      = false;
    mRunning          = true;
    mErrorCode        = 0;
    mFlagShowFPSTitle = false;

    ProfileBlock();

    if (Dir::exists(ENGINE_DEFAULTS::DATA_PATH) == false) {
        LOG << Log::CRITICAL
            << "[MedievalEngine::MedievalEngine] Data directory not found "
            << ENGINE_DEFAULTS::DATA_PATH << std::endl;

        this->close(4);
        return;
    }

    LuaAPI::loadLibs();

    // We verify if a config argument has been passed, if so we load the engine
    // with the specified configuration file
    if (mArguments.hasArgument("config")) {
        mConfigurations.readFile(mArguments.getArgument("config"));
    } else {
        // Read the default configuration file
        if (!mConfigurations.readFile(ENGINE_DEFAULTS::CONFIG_FILE)) {
            LOG << Log::CRITICAL
                << "[MedievalEngine::MedievalEngine] Could not find the configuration file "
                << ENGINE_DEFAULTS::CONFIG_FILE << std::endl;

            this->close(5);
            return;
        }
    }


    String width;
    String height;
    String bitsPerPixel;
    String fullScreen;
    String windowName;
    String language;
    String globalVolume;
    String voiceVolume;
    String musicVolume;
    String ambientVolume;
    String vsync;
    String frameLimit;

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
        mWindowInfoInput.bitsPerPixel = static_cast<uint8>(Kit::string_int(bitsPerPixel));
    } else {
        mConfigurations.add("bits_per_pixels", Kit::int_string(ENGINE_DEFAULTS::BITS_PER_PIXEL_WINDOW));
    }

    if(height != "") {
        mWindowInfoInput.height = static_cast<uint16>(Kit::string_int(height));
    } else {
        mConfigurations.add("height", Kit::int_string(ENGINE_DEFAULTS::HEIGHT_WINDOW));
    }

    if(width != "") {
        mWindowInfoInput.width = static_cast<uint16>(Kit::string_int(width));
    } else {
        mConfigurations.add("width", Kit::int_string(ENGINE_DEFAULTS::WIDTH_WINDOW));
    }

    if(fullScreen != "") {
        mWindowInfoInput.fullScreen = Kit::string_bool(fullScreen);
    } else {
        mConfigurations.add("fullscreen", Kit::bool_string(ENGINE_DEFAULTS::FULLSCREEN_WINDOW));
    }

    if(vsync != "") {
        mWindowInfoInput.vsync = Kit::string_bool(vsync);
    } else {
        mConfigurations.add("vsync", Kit::bool_string(ENGINE_DEFAULTS::VSYNC));
    }

    if(frameLimit != "") {
        mWindowInfoInput.frameLimit = static_cast<uint16>(Kit::string_int(frameLimit));
    } else {
        mConfigurations.add("frame_limit", Kit::int_string(ENGINE_DEFAULTS::FRAME_LIMIT));
    }

    if (windowName != "") {
        if (windowName == "$fps") {
            mFlagShowFPSTitle = true;
        }

        mWindowInfoInput.windowName = windowName;
    } else {
        mConfigurations.add("engine_name", String(ENGINE_DEFAULTS::ENGINE_NAME));
    }

    // Max volume 100.f
    if (globalVolume != "") {
        Audible::GLOBAL_VOLUME = std::min(Kit::string_float(globalVolume), 100.f);
    } else {
        mConfigurations.add("global_volume", Kit::float_string(Audible::GLOBAL_VOLUME));
    }

    if (voiceVolume != "") {
        Audible::VOICE_VOLUME = std::min(Kit::string_float(voiceVolume), 100.f);
    } else {
        mConfigurations.add("voice_volume", Kit::float_string(Audible::VOICE_VOLUME));
    }

    if (musicVolume != "") {
        Audible::MUSIC_VOLUME = std::min(Kit::string_float(musicVolume), 100.f);
    } else {
        mConfigurations.add("music_volume", Kit::float_string(Audible::MUSIC_VOLUME));
    }

    if (ambientVolume != "") {
        Audible::AMBIENT_VOLUME = std::min(Kit::string_float(ambientVolume), 100.f);
    } else {
        mConfigurations.add("ambient_volume", Kit::float_string(Audible::AMBIENT_VOLUME));
    }

    // Try to open the language file specified on the configuration file
    // If we failed to load the language file or its not informed on the configuration file
    // we try to load the default language file
    if (language == "" || !Strings::openLanguageFile(ENGINE_DEFAULTS::LANG_PATH + language.getString())) {
        // If we failed to open the default language file we close the engine
        if (!Strings::openLanguageFile(ENGINE_DEFAULTS::LANG_PATH + ENGINE_DEFAULTS::LANGUAGE)) {
            LOG << Log::CRITICAL
                << "[MedievalEngine::MedievalEngine] Could not get the default language pack "
                << ENGINE_DEFAULTS::LANG_PATH + ENGINE_DEFAULTS::LANGUAGE
                << " neither the language specific "
                << language.getString() << std::endl;

            this->close(3);
            return;
        }
    }


    // Try to open the default engine data file
    // If we cant open it we close the engine
    if (!mDataFiles.openFile(ENGINE_DEFAULTS::DATA_PATH +
                             ENGINE_DEFAULTS::DEFAULT_DATFILE)) {
        LOG << Log::CRITICAL
            << "[MedievalEngine::MedievalEngine] Could not open the default assets file "
            << ENGINE_DEFAULTS::DEFAULT_DATFILE.c_str() << std::endl;

        this->close(1);
    } else {
        // If we can open the file but the signature its different we close the engine as well
        if (mDataFiles.getName() == ENGINE_DEFAULTS::DATFILE_SIGNATURE_NAME &&
            mDataFiles.getVersion() == ENGINE_DEFAULTS::DATFILE_SIGNATURE_VERSION ) {

            // Load the default engine font for the engine, its the fallback font for all the
            // string related stuff
            if(ResourceManager::loadFont("default_font", mDataFiles.getFile("default.ttf"),
                                        mDataFiles.getFileEntrySize("default.ttf"))) {
                Font::Default = "default_font";    
            } else {
                LOG << Log::CRITICAL << "[MedievalEngine::MedievalEngine] Could not open the default font"
                    << std::endl;   

                this->close(6);
                return;    
            }
            

            LOG << Log::VERBOSE
                << "[MedievalEngine::MedievalEngine] Default font loaded "
                << std::endl;
        } else {
            LOG << Log::CRITICAL << "[MedievalEngine::MedievalEngine] Default asset pack not recognized "
            << ENGINE_DEFAULTS::DEFAULT_DATFILE.c_str() << std::endl;

            this->close(2);
            return;
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

    // mGameStates.add("menu", new MenuScreen());

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
        if (ResourceManager::loadFont(mConfigurations.getKey("game_font").getString())) {
            Font::GameFont = mConfigurations.getKey("game_font").getString(); 
        } else {
            Font::GameFont = Font::Default;
        }
    }

    // We create the window here so We dont have any freeze on the screen
    mWindow.create(mWindowInfoInput);

    mGameStates.push(new LoadingScreen());
    // mGameStateManager.getGameState("loading")->registerEngine(this);
    // mGameStateManager.setGameState("loading");

    // Open the window only after the loading screen has been initialized
    mWindow.open();


    // Register the engine on our console
    mConsole.registerEngine(this);


    // Set an icon and cursor if we find it on the configuration file
    std::string iconName;
    std::string cursorName;
    iconName   = mConfigurations.getKey("icon").getString();
    cursorName = mConfigurations.getKey("cursor").getString();

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
    LuaExportAPI::exports("engine_close", "[int error_code]", "void", LuaExportType::FUNCTION, "close the engine from the console or game script code");

    LuaAPI::state.set_function("engine_is_running", &MedievalEngine::isRunning, this);
    LuaExportAPI::exports("engine_is_running", "", "bool", LuaExportType::FUNCTION, "return if the engine is current running or not");

    LuaAPI::state.set_function("engine_is_loading_thread_done", &MedievalEngine::isLoadingThreadDone, this);
    LuaExportAPI::exports("engine_is_loading_thread_done", "", "bool", LuaExportType::FUNCTION, "if the loading thread is done loading, meaning that the engine must be on the first game state(menu)");

    LuaAPI::state.set_function("engine_save_config_file", [this]() {
        mConfigurations.save();
    });
    LuaExportAPI::exports("engine_save_config_file", "", "void", LuaExportType::FUNCTION, "save the current configuration to the config file");



    LuaAPI::state.set_function("audio_get_global_volume", []() -> float {
        return Audible::GLOBAL_VOLUME;
    });
    LuaExportAPI::exports("audio_get_global_volume", "", "float", LuaExportType::FUNCTION,
                            "get the engine global audio volume");

    LuaAPI::state.set_function("audio_get_voice_volume", []() -> float {
        return Audible::VOICE_VOLUME;
    });
    LuaExportAPI::exports("audio_get_voice_volume", "", "float", LuaExportType::FUNCTION,
                            "get the engine voice audio volume");

    LuaAPI::state.set_function("audio_get_music_volume", []() -> float {
        return Audible::MUSIC_VOLUME;
    });
    LuaExportAPI::exports("audio_get_music_volume", "", "float", LuaExportType::FUNCTION,
                            "get the engine music audio volume");

    LuaAPI::state.set_function("audio_get_ambient_volume", []() -> float {
        return Audible::AMBIENT_VOLUME;
    });
    LuaExportAPI::exports("audio_get_ambient_volume", "", "float", LuaExportType::FUNCTION,
                            "get the engine ambient audio volume");

    LuaAPI::state.set_function("audio_set_global_volume", [this](float volume) {
        Audible::GLOBAL_VOLUME = volume;
        ResourceManager::updateAudibleVolume();
    });
    LuaExportAPI::exports("audio_set_global_volume", "", "float", LuaExportType::FUNCTION,
                            "set the engine global audio volume");

    LuaAPI::state.set_function("audio_set_voice_volume", [this](float volume) {
        Audible::VOICE_VOLUME = volume;
        ResourceManager::updateAudibleVolume();
    });
    LuaExportAPI::exports("audio_set_voice_volume", "", "float", LuaExportType::FUNCTION,
                            "set the engine voice audio volume");

    LuaAPI::state.set_function("audio_set_music_volume", [this](float volume) {
        Audible::MUSIC_VOLUME = volume;
        ResourceManager::updateAudibleVolume();
    });
    LuaExportAPI::exports("audio_set_music_volume", "", "float", LuaExportType::FUNCTION,
                            "set the engine music audio volume");

    LuaAPI::state.set_function("audio_set_ambient_volume", [this](float volume) {
        Audible::AMBIENT_VOLUME = volume;
        ResourceManager::updateAudibleVolume();
    });
    LuaExportAPI::exports("audio_set_ambient_volume", "", "float", LuaExportType::FUNCTION,
                            "set the engine ambient audio volume");
    
}

void MedievalEngine::run() {
    if (!isRunning()) {
        return;
    }

    ProfileBlock();
    while(mWindow.isOpen() && isRunning()) {
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
                    mGameStates.handleEvents(event);
                }

                // handle the console events, since it's independent
                mConsole.handleEvents(event);
            }
        }

        {
            ProfileBlockStr("update game state");
            mGameStates.update(mWindow.getDelta());
        }

        {
            ProfileBlockStr("window clear");
            mWindow.clear();
        }

        {
            ProfileBlockStr("draw game state");
            mGameStates.draw(mWindow);
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

        if (mFlagShowFPSTitle) {
            ProfileBlockStr("window set title fps");
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

void MedievalEngine::setCurrentMusicQueue(const std::string &name) {
    mCurrentMusicQueue = name;
}

MusicQueue* MedievalEngine::getMusicQueue(const std::string &name) {
    // If we dont find any music queue we just create one
    // and register our engine on it
    if (!(mMusicQueue.find(name) != mMusicQueue.end())) {
        LOG << Log::VERBOSE << "[MedievalEngine::getMusicQueue] "
            << "Muisc Queue " + name + " not found, creating new Music Queue" << std::endl;

        mMusicQueue[name] = MusicQueue();
    }

    return &mMusicQueue[name];
}

void MedievalEngine::close(const int &errorCode) {
    LOG << Log::VERBOSE << "[MedievalEngine::close]" << std::endl;
    mRunning = false;
    mErrorCode = errorCode;

    // Wait for the thread to finish the loading
    // if we dont the engine crash horrible
    if (mLoadingThread.joinable()) {
        mLoadingThread.join();
    }

}

Window* MedievalEngine::getWindow() {
    return &mWindow;
}


GameStateManager* MedievalEngine::getGameStateManager() {
    return &mGameStates;
}

DATFile* MedievalEngine::getDATAFileHandle() {
    return &mDataFiles;
}

MedievalEngine::~MedievalEngine() {
    ResourceManager::clear();
    LOG << Log::VERBOSE << "[MedievalEngine::~MedievalEngine]" << std::endl;
}
