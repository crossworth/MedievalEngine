#ifndef MEDIEVALENGINE_MEDIEVALENGINE_H_
#define MEDIEVALENGINE_MEDIEVALENGINE_H_

#include "Lua/LuaConsole.h"

#include "Helper/DATFile.h"
#include "Helper/Strings.h"
#include "Helper/ArgumentsParser.h"


#include "GameState/GameStateManager.h"

namespace ME {

class MedievalEngine {
public:
    MedievalEngine(int argc, char **argv);
    void init();
    void run();
    void close(const int &errorCode = 0);
    int getErrorCode();
    bool isRunning();

    Window* getWindow();
    GameStateManager* getGameStateManager();
    DATFile* getDATAFileHandle();
    MusicQueue* getMusicQueue(const std::string &name);
    void setCurrentMusicQueue(const std::string &name);

    ~MedievalEngine();

    bool isLoadingThreadDone();

private:
    void setLoadingThreadDone();
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
    CFGParser mConfigurations;
    ArgumentsParser mArguments;
    DATFile mDataFiles;
    GameStateManager mGameStates;
};

}

#endif // MEDIEVALENGINE_MEDIEVALENGINE_H_

