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
    Window mWindow;
    AssetsManager *mAssetsManager;
    CFGParser mConfigurations;
    static MedievalEngine* mInstance;
    MedievalEngine(int argc, char **argv);
};

}

#endif // MEDIEVALENGINE_H
