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
 * EFFECTS <-- BROKEN
 * - Verify everything!!!
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
 * LUA LANGUAGE AND CONSOLE
 * - Create an interface with only one virtual method called something like exposeLua
 * - Most the classes will be implementing this method and will expose functions to the LUA
 * - Create a console interface which we will be able to call any of the exposed method's
 * - like show_debug
 * - use underscore on the lua land
 */

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

    ProfileBlock();

    ME::MedievalEngine app(argc, argv);
    app.init();
    app.run();
    app.close();

    return app.getErrorCode();
}
