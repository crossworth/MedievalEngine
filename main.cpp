#include "GameEngine.h"

int main(int argc,char **argv) {

    ProfileInit();
    ProfileStart();

    ME::GameEngine *app = ME::GameEngine::getInstance(argc,argv);
    app->init();

    app->run();
    app->clear();
    int EXIT_CODE = app->onExit();


    ProfileEnd("GameEngine total");

    return EXIT_CODE;
}

