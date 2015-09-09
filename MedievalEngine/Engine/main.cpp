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

/**
 * Cool profiler idea
 *
 * make a clas that have only two method the constructor and the destructor
 * the constructor just store the time that it was constructed
 * and the destructor compare the time
 *
 * and we could do something like
 *
 * RECORD_BLOCK(); as a macro
 *
 * which would call somethig like
 *
 *
 * Profile(__LINE__, __FUNCTION__, __FILE__)
 *
 * or something like that
 */

#include "Helper/Profiler.h"
#include "Engine/MedievalEngine.h"
#include <iostream>


/**
 * Main entry point for the game engine
 *
 * @param  argc You know what it is
 * @param  argv If don't, get out of there
 * @return      Error code
 */
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
