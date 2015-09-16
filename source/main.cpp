/**
 * Medieval Engine 2015
 * Pedro Henrique - system.pedrohenrique@gmail.com
 *
 * MEDIEVAL ENGINE TODO LIST
 *
 * GENERAL
 * - Better logging (put more logging call on the methods) 
 * - Comment the code
 * - Documentation the code
 * - Resource improve on failed to load resource (open a default_failed_to_load file like Valve Engine)
 * - Memory (free all the pointers)
 * - Debugger (show mouse position, fps, current game state, currente game state status, memory usage, music playing)
 * - maps key's to event's <!! IMPORTANT
 * - improve all the loading resources, with a custom fail to load texture or text
 * - or event sound to show use as fallback when something don't load properly
 *
 * GUI
 * - Add focus support for the GUI elements
 * - Z-index on elements? or disable events
 * - Fix size, bounds, position, rotate
 *
 * OPTIONS SCREEN
 * - Update the volume of all the Music's queue's based on the configuration state
 * - Update the resolution of all the textures and images based on the screen size definied
 *
 *
 *
 */

#include "Engine/MedievalEngine.h"


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