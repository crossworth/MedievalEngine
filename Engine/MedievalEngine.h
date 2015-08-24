#ifndef MEDIEVALENGINE_H
#define MEDIEVALENGINE_H
#include <Headers.h>


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
    AssetsManager* getAssetsManager();
    GameStateManager* getGameStateManager();
    GUI* getGUI();
    SM::DATFile* getDATAFileHandle();

    ~MedievalEngine();
private:

    int mErroCode;
    Window mWindow;
    GUI mGUI;
    AssetsManager mAssetsManager;
    CFGParser mConfigurations;
    ArgumentsParser mArguments;
    SM::DATFile mDataFiles;
    GameStateManager mGameStateManager;
};

}

#endif // MEDIEVALENGINE_H
