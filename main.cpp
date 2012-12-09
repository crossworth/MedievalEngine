#include "gameengine.h"


int main()
{
    ProfileInit();
    ProfileStart();
    ME::gameEngine *app = ME::gameEngine::getInstance();
    app->init();

    app->run();
    app->clear();

    ProfileEnd("Execucao total Engine");
    return 0;
}

