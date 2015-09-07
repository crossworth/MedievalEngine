/**
 * Medieval Engine 2015
 * Pedro Henrique - system.pedrohenrique@gmail.com
 *
 * All files should be using the ISO 8859-1 enconding
 *
 * MEDIEVAL ENGINE TODO LIST
 *
 * GENERAL
 * - Better logging (put more logging call on the methods, improve time stamp, line number and file name)
 * - Better profiler
 * - Comment the code
 * - CFGParser enable array's
 * - Documentation the code
 * - Resource improve on failed to load resource (open a default_failed_to_load file like Valve Engine)
 * - Memory (free all the pointers)
 *
 * EFFECTS
 * - Verify the shader class if everything works
 *
 * GUI
 * - Add focus support for the GUI elements
 * - Fix size, bounds, position, rotate
 *
 * OPTIONS SCREEN
 * - Update the volume of all the Music's queue's based on the configuration state
 * - Update the resolution of all the textures and images based on the screen size definied
 *
 *
 */

#include "Helper/Profiler.h"
#include "Engine/MedievalEngine.h"
#include <iostream>



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
