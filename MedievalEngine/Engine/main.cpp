#include "Helper/Profiler.h"
#include "Engine/MedievalEngine.h"
#include <iostream>

/**
* Medieval Engine 2015
* Pedro Henrique - system.pedrohenrique@gmail.com
*
* All the files are using ISO 8859-1 file enconding
**/


/**
*   TODOS
* - String manipulation class, so We can use something like Kit::getStr("loading_text")
* - Some kind of normalization of the size of the images for diferentes screens
*
*
*
*
**/

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
