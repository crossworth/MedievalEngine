#include <Headers.h>
#include <Helper/Profiler.h>
#include <Engine/MedievalEngine.h>

int main(int argc, char **argv) {

    ProfileInit();
    ProfileStart();

    ME::MedievalEngine *app = ME::MedievalEngine::getInstance(argc, argv);
    app->init();
    app->run();
    app->close();

    ProfileEnd("GameEngine total");
    return 0;
}

