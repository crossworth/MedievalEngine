#ifndef ENGINE_CONFIG_H
#define ENGINE_CONFIG_H
#include <map>
#include <vector>
#include <fstream>
#include "Helper/Dir.h"

/**
 * @namespace ME
 * @brief The Global Medieval Engine namespace
 *
 * All the Medieval Engine code it's on the ME namespace
 */
namespace ME {

/**
 * @namespace ME::ENGINE_DEFAULTS
 * @brief The namespace for the default configurations variables and constants
 *
 * All the default configurations are placed on this namespace, all the user defined
 * variables and constants must be here for a fallback case.
 */
namespace ENGINE_DEFAULTS {

    /**
     * Default engine name or game name usued if the engine name it's
     * not provied on the configuration file<br>
     * Constant fallback to "Medieval Engine"
     */
    const std::string ENGINE_NAME = "Medieval Engine";

    /**
     *  Engine version<br>
     *  Constant fallback
     */
    const float ENGINE_VERSION = 1.3f;

    /**
     * Default window width<br>
     * Constant fallback to 700
     */
    const int WIDTH_WINDOW = 700;

    /**
     * Default window height<br>
     * Constant fallback to 500
     */
    const int HEIGHT_WINDOW = 500;

    /**
     * Default bits per pixel<br>
     * Constant fallback to 32
     */
    const int BITS_PER_PIXEL_WINDOW = 32;

    /**
     * If the game should be fullscreen or not<br>
     * NOTE(Pedro): To be a valid fullscreen it's must
     * first verify if the current computer accepet the
     * specified resolution<br>
     * Constant fallback to false
     */
    const bool FULLSCREEN_WINDOW = false;

    /**
     * The default frame limit for the Engine<br>
     * This can be changed and don't have any side effect on the game loop<br>
     * Constant fallback to 0 (unlimited)
     */
    const int FRAME_LIMIT = 0;

    /**
     * If we wait for the vertical synchronization<br>
     * Constant falback to true
     */
    const bool VSYNC = true;

    /**
     *  The global Path of the executable
     */
    const std::string GLOBAL_PATH = ME::Dir::getCurrentPath();

    /**
     * The default path to the data folder<br>
     * Default GLOBAL_PATH + "/data/"
     */
    const std::string DATA_PATH = GLOBAL_PATH + "/data/";

    /**
     * The default path to the assets folder<br>
     * Default DATA_PATH + "assets/"
     */
    const std::string ASSETS_PATH = DATA_PATH + "assets/";

    /**
     * The default path to the shaders folder<br>
     * Default ASSETS_PATH + "shaders/"
     */
    const std::string SHADER_PATH = ASSETS_PATH + "shaders/";

    /**
     * The default path to the language folder<br>
     * Default  DATA_PATH + "lang/"
     */
    const std::string LANG_PATH = DATA_PATH + "lang/";

    /**
     * The default language and fallback language file<br>
     * Default to "english.lang"
     */
    const std::string LANGUAGE = "english.lang";

    /**
     * The default path and name of the configuration file<br>
     * Default to DATA_PATH + "config.cfg"
     */
    const std::string CONFIG_FILE = DATA_PATH + "config.cfg";

    /**
     * The default DAT file with the required resources<br>
     * Default to "base.dat"<br>
     * NOTE(Pedro): on the loading procedure it's try to open
     * DATA_PATH + DEFAULT_DATFILE
     */
    const std::string DEFAULT_DATFILE = "base.dat";

    /**
     * The default signature name of the DAT file
     * Default to "Default Asset Pack"<br>
     * NOTE(Pedro): this will only be usued on the DEFAULT_DATFILE
     * all the other files will not have a signature check
     */
    const std::string DATFILE_SIGNATURE_NAME = "Default Asset Pack";

    /**
     * The default signature version for the DAT file<br>
     * Default to "1.0.0" - NOTE(Pedro): this should be a string<br>
     * NOTE(Pedro): this will only be usued on the DEFAULT_DATFILE
     * all the other files will not have a signature check
     */
    const std::string DATFILE_SIGNATURE_VERSION = "1.0.0";

    /**
     * The default Keys Mapper for the enginebr>
     * Default to "keys.cfg"<br>
     * NOTE(Pedro): on the loading procedure it's try to open
     * GLOBAL_PATH + DEFAULT_KEY_MAPPER
     */
    const std::string DEFAULT_KEY_MAPPER = DATA_PATH + "keys.cfg";

    /**
     * The default base width for the engine<br>
     * If you're creating art work on a photoshop file with
     * the size of 1920x1080 the base width should be 1920<br>
     * This way if someone try to open the game on a different
     * screen size we can calcule the right scale for the Drawable objects<br>
     * This requires that the art work are relative to this size
     */
    const int BASE_WIDTH_SIZE = 1920;

    /**
     * The default base height for the engine<br>
     * If you're creating art work on a photoshop file with
     * the size of 1920x1080 the base height should be 1080<br>
     * This way if someone try to open the game on a different
     * screen size we can calcule the right scale for the Drawable objects<br>
     * This requires that the art work are relative to this size
     */
    const int BASE_HEIGHT_SIZE = 1080;

    /**
     * The default global volume for the engine<br>
     * Default to 100.f
     */
    const float DEFAULT_VOLUME = 100.f;

    /**
     * The default music volume for the engine<br>
     * Default to 100.f
     */
    const float MUSIC_VOLUME = 100.f;

    /**
     * The default voice volume for the engine<br>
     * Default to 100.f
     */
    const float VOICE_VOLUME = 100.f;

    /**
     * The default ambient volume for the engine<br>
     * Default to 100.f
     */
    const float AMBIENT_VOLUME = 100.f;
}

// TODO(pedro): move this to the namespace
const bool _LOG_WRITE_TO_FILE    = false;
const std::string _LOG_FILE_NAME = "output.log";

}




#endif // ENGINE_CONFIG_H
