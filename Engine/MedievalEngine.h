#ifndef MEDIEVALENGINE_H
#define MEDIEVALENGINE_H
#include <Headers.h>


namespace ME {

class MedievalEngine {
public:
    static MedievalEngine* getInstance(int argc = 0, char** argv = nullptr);

    void init();
    void run();
    void close();

    Window* getWindow();
    AssetsManager* getAssetsManager();
    GameStateManager* getGameStateManager();
    GUI* getGUI();
    SM::DATFile* getDATAFileHandle();

    ~MedievalEngine();
private:
    Window mWindow;
    GUI* mGUI;
    AssetsManager mAssetsManager;
    CFGParser mConfigurations;
    ArgumentsParser mArguments;
    SM::DATFile* mDataFiles;
    GameStateManager mGameStateManager;
    static MedievalEngine* mInstance;
    MedievalEngine(int argc, char **argv);
};

}

#endif // MEDIEVALENGINE_H
