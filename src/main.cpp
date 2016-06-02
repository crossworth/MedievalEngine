/**
 * Medieval Engine 2015
 * Pedro Henrique - system.pedrohenrique@gmail.com
 *
 * MEDIEVAL ENGINE TODO LIST
 *
 * Fix space to tab on all files
 * Fix all the header's include name
 * 
 * GENERAL
 * - Better logging (put more logging call on the methods)
 * - Comment the code
 * - Documentation the code
 * - Resource improve on failed to load resource (open a default_failed_to_load file like Valve Engine)
 * - Memory (free all the pointers)
 * - Debugger (show mouse position, fps, current game state, currente game state status, memory usage, music playing)
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


int main(int argc, char** argv) {

    ProfileBlock();

    ME::MedievalEngine app(argc, argv);
    app.init();
    app.run();

    return app.getErrorCode();
}
