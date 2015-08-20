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

    ~MedievalEngine();
private:
    Window mWindow;
    GUI *mGUI;
    AssetsManager *mAssetsManager;
    CFGParser mConfigurations;
    ArgumentsParser mArguments;
    GameStateManager mGameStateManager;
    static MedievalEngine* mInstance;
    MedievalEngine(int argc, char **argv);
};

}

#endif // MEDIEVALENGINE_H
