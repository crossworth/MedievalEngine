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
private:
    MEid idSound;
    Sprite* spriteObj;
    Text* textObj;
    SpriteAnimation* marioSptAn;
    Window mWindow;
    AssetsManager *mAssetsManager;
    CFGParser mConfigurations;
    ArgumentsParser mArguments;
    static MedievalEngine* mInstance;
    MedievalEngine(int argc, char **argv);
};

}

#endif // MEDIEVALENGINE_H
