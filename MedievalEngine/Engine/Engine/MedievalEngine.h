#ifndef MEDIEVALENGINE_H
#define MEDIEVALENGINE_H
#include <algorithm>
#include "Headers.h"

namespace ME {

class MedievalEngine {
public:
    MedievalEngine(int argc, char **argv);
    void init();
    void run();
    void close();
    int getErrorCode();
    bool isRunning();

    Window* getWindow();
    ResourceManager* getResourceManager();
    GameStateManager* getGameStateManager();
    GUI* getGUI();
    DATFile* getDATAFileHandle();

    ~MedievalEngine();

    ResourceID gameFontID;
private:
    int mErrorCode;
    Window mWindow;
    GUI mGUI;
    ResourceManager mResourceManager;
    CFGParser mConfigurations;
    ArgumentsParser mArguments;
    DATFile mDataFiles;
    GameStateManager mGameStateManager;
};

}

#endif // MEDIEVALENGINE_H
