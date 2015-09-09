#ifndef MEDIEVALENGINE_H
#define MEDIEVALENGINE_H
#include <algorithm> // TODO(Pedro): Do we need this?
#include <thread>
#include "Helper/Profiler.h"
#include "Headers.h"

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

    // TODO(Pedro): Rename to GAME_FONT_ID and make it static
    ResourceID gameFontID;

    // TODO(Pedro): Could this be private?
    bool doneLoading();
    void loadingThread();

// TODO(Pedro): Could this be private as well?
protected:
    bool mDoneLoading;
    std::thread* mLoadingThread;
private:
    std::string mCurrentMusicQueue;
    std::map<std::string, MusicQueue> mMusicQueue;
    bool mRunning;
    int mErrorCode;
    Window mWindow;
    // TODO(Pedro): Rename this variable to mWindowInfoInput
    WindowInfo mWindowInfo_;
    ResourceManager mResourceManager;
    CFGParser mConfigurations;
    ArgumentsParser mArguments;
    DATFile mDataFiles;
    GameStateManager mGameStateManager;
};

}

#endif // MEDIEVALENGINE_H
