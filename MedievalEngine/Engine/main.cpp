#include "Helper/Profiler.h"
#include "Engine/MedievalEngine.h"




int main(int argc, char** argv) {
    ProfileInit();
    ProfileStart();

    ME::MedievalEngine app(argc, argv);
    app.init();
    app.run();
    app.close();

    ProfileEnd("GameEngine total");


    return app.getErrorCode();
}
