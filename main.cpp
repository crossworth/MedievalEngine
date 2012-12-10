#include "gameengine.h"

int main(int argc,char **argv)
{

    ProfileInit();
    ProfileStart();


    ME::gameEngine *app = ME::gameEngine::getInstance(argc,argv);
    app->init();

    app->run();
    app->clear();
    int EXIT_CODE = app->onExit();


    ProfileEnd("Execucao total Engine");

    return EXIT_CODE;
}

