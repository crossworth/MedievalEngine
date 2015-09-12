#ifndef MEDIEVALENGINE_H
#define MEDIEVALENGINE_H
#include <thread>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include "Helper/Profiler.h"
#include "Helper/DATFile.h"
#include "Helper/ArgumentsParser.h"
#include "Helper/Strings.h"
#include "Effects/Fade.h"
#include "Effects/Strobe.h"
#include "Effects/Shader.h"
#include "GameState/GameStateManager.h"
#include "Lua/LuaAPI.h"
#include "Lua/LuaConsole.h"


namespace ME {

class MedievalEngine {
public:
    MedievalEngine(int argc, char** argv);
    void init();
    void run();
    void close();
    int getErrorCode();
    bool isRunning();

    Window* getWindow();
    ResourceManager* getResourceManager();
    GameStateManager* getGameStateManager();
    DATFile* getDATAFileHandle();
    MusicQueue* getMusicQueue(const std::string& name);
    void setCurrentMusicQueue(const std::string& name);

    ~MedievalEngine();

    ResourceID GAME_FONT_ID;

    bool isLoadingThreadDone();

private:
    void loadingThread();

    bool mDoneLoading;
    std::thread mLoadingThread;

    std::string mCurrentMusicQueue;
    std::map<std::string, MusicQueue> mMusicQueue;
    bool mRunning;
    int mErrorCode;
    Window mWindow;
    LuaConsole mConsole;
    
    WindowInfo mWindowInfoInput;
    ResourceManager mResourceManager;
    CFGParser mConfigurations;
    ArgumentsParser mArguments;
    DATFile mDataFiles;
    GameStateManager mGameStateManager;
};

}

#endif // MEDIEVALENGINE_H
