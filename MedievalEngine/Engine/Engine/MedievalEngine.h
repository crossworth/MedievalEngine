#ifndef MEDIEVALENGINE_H
#define MEDIEVALENGINE_H
#include <algorithm>
#include <thread>
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

    ResourceID gameFontID;

    bool doneLoading();
    void loadingThread();
protected:
    bool mDoneLoading;
    std::thread* mLoadingThread;
private:
    std::string mCurrentMusicQueue;
    std::map<std::string, MusicQueue> mMusicQueue;
    bool mRunning;
    int mErrorCode;
    Window mWindow;
    WindowInfo mWindowInfo_;
    ResourceManager mResourceManager;
    CFGParser mConfigurations;
    ArgumentsParser mArguments;
    DATFile mDataFiles;
    GameStateManager mGameStateManager;
};

}

#endif // MEDIEVALENGINE_H
