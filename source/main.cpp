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
 * - maps key's to event's
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
 * LUA LANGUAGE AND CONSOLE
 * - Create an interface with only one virtual method called something like exposeLua
 * - Most the classes will be implementing this method and will expose functions to the LUA
 * - Create a console interface which we will be able to call any of the exposed method's
 * - like show_debug
 * - use underscore on the lua land
 *
 * class LuaAPI {
 * public:
 *     static void setVariable('name', value);
 *     static T getVariable();
 *     static void setTable(); // HOW to do this?
 *     static void bindFunction('name', &Class::function);
 *     static void bindFunction('name', &Class::function, object); // Will this work?
 *     static void bindFunction('name', function);
 * private:
 *     static LuaAPI mLuaAPI; // Thread safe? Atomic?
 * };
 *
 * class LuaExpose {
 * public:
 *     virtual void exposeLua() = 0;
 * };
 *
 * class Drawable: public LuaExpose {
 * 	   void setPosition(int x, int y);
 *
 *     void exposeLua() {
 *         LuaAPI::setVariable('engine_name', 'Medieval Engine');
 *
 *
 *
 *     }
 * };
 *
 * Call the functions or make a command interpreter, or just expose the LUA script
 * profiler_toggle           // command call a function
 * profiler_set_time seconds // command call the function with seconds as parameter
 * window.width              // print the variable window size
 * mVar = 10                 // assign 10 to variable mVar
 *
 * //TODO(Pedro):
 * On the draw function draw the console, the profiler, the log and the debug
 *
 * LUA EXPOSED API
 * - interactive_mode_toggle() // Enable or disable the interactive mode of the console
 * - profiler_toggle()
 * - profiler_set_time
 * - log_toggle()        // Toggle the log to the screen
 * - debug_toggle() (FPS, debug_file, memory usage, object that are being drawing, music playing)
 * - is_custom_cursor() // Must be a function since this can be changed duruing runtime
 * - is_shader_enable()
 * - window_height()         // Or get a table window.size or both
 * - window_bits_per_pixel()
 * - window_vsyn()
 * - The sprite, music, and stuff don't need to be implemented yet just the console mode
 * -
 * -
 * -
 * -
 * -
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
