#include <Headers.h>
#include <Helper/Profiler.h>
#include <Engine/MedievalEngine.h>

#ifdef TEST
#define CATCH_CONFIG_RUNNER
#include <ThirdParty/Catch.h>
#endif

int main(int argc, char **argv) {
    int resultCode = 0;

    #ifdef TEST
    resultCode = Catch::Session().run(argc, argv);
    #endif

    ProfileInit();
    ProfileStart();

    ME::MedievalEngine app(argc, argv);
    app.init();
    app.run();
    app.close();

    ProfileEnd("GameEngine total");
    return resultCode;
}

