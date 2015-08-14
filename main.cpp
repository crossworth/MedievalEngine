#include <Headers.h>
#include <Helper/Profiler.h>

int main(int argc,char **argv) {

    ProfileInit();
    ProfileStart();

//    ME::GameEngine *app = ME::GameEngine::getInstance(argc,argv);
//    app->init();

//    app->run();
//    app->clear();
//    int EXIT_CODE = app->onExit();

    ME::AssetsManager* assets = ME::AssetsManager::getInstance();

    assert(assets != nullptr);

    ME::MEid mID = assets->loadTexture("icon.png");


    ProfileEnd("GameEngine total");

//    return EXIT_CODE;
    return 0;
}

