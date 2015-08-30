#ifndef ENGINE_CONFIG_H
#define ENGINE_CONFIG_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "Helper/Dir.h"

namespace ME {

namespace ENGINE_DEFAULTS {

    // GLOBAL
    const std::string ENGINE_NAME = "Medieval Engine";
    const float ENGINE_VERSION    = 1.3f;

    const int WIDTH_WINDOW            = 700;
    const int HEIGHT_WINDOW           = 500;
    const int BITS_PER_PIXEL_WINDOW   = 32;
    const bool FULLSCREEN_WINDOW      = false;
    const int FRAME_LIMIT             = 60;
    const bool VSYNC                  = true;

    const std::string GLOBAL_PATH = ME::Dir::getCurrentPath();
    const std::string DATA_PATH   = GLOBAL_PATH + "/data/";
    const std::string ASSETS_PATH = DATA_PATH + "assets/";

    const std::string SHADER_PATH = ASSETS_PATH + "shaders/";

    const std::string CONFIG_FILE     = DATA_PATH + "config.cfg";
    const std::string DEFAULT_DATFILE = "base.dat";

    const std::string DATFILE_SIGNATURE_NAME    = "Default Asset Pack";
    const std::string DATFILE_SIGNATURE_VERSION = "1.0.0";


}

/**
 * Uncomment the line to log file name and line numbers
 * */
// #define LOG_FILE_NUMBERS

const bool _LOG_WRITE_TO_FILE    = false;
const std::string _LOG_FILE_NAME = "output.log";

}

#ifndef nullptr
#define nullptr 0
#endif



#endif // ENGINE_CONFIG_H
