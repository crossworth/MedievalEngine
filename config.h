#ifndef ENGINE_CONFIG_H
#define ENGINE_CONFIG_H
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <assert.h>
#include <exception>
#include <QDir>
#include <QtCore/qstring.h>
#include <QtCore/qfileinfo.h>
#include <QtCore/qstringlist.h>
#include "key.h"

namespace ME {

class gameEngine;


namespace ENGINE_DEFAULTS {

    // GLOBAL
    const std::string ENGINE_NAME = "Medieval Engine";
    const float ENGINE_VERSION    = 1.1f;

    const int WIDTH_WINDOW          = 700;
    const int HEIGHT_WINDOW         = 500;
    const int BITS_PER_PIXEL_WINDOW = 32;
    const bool FULLSCREEN_WINDOW    = false;
    const int FRAME_LIMIT           = 60;
    const bool VSYNC                = true;


    const std::string CONFIG_FILE = "config.cfg";
}

const QDir GLOBAL_DIR;
const std::string GLOBAL_PATH = GLOBAL_DIR.absolutePath().toStdString() + "/";

// DEBUG INFO
const bool DEBUG             = true;
const std::string DEBUG_FILE = "";
const bool DEBUG_LUA_VERBOSE = false;
enum debug_type {LUA_VERBOSE = 0, VERBOSE, WARNING, CRITICAL };

// ASSETS MANAGER
const bool DEBUG_LOADING_ASSETS = false;
enum ASSETS_TYPE { TEXTURE = 0, SPRITE, SOUND, MUSIC, IMAGE, FONT, RECTANGLESHAPE, TEXT, BINARY};

// DECOUPLING SFML

// Tipos de assets
typedef sf::Texture Texture;
typedef sf::Sprite Sprite;
typedef sf::Music Music;
typedef sf::Sound Sound;
typedef sf::Image Image;
typedef sf::Font Font;
typedef sf::Text Text;
typedef sf::RectangleShape RectangleShape;

// Estruturas com informações de cada asset

struct TextureAsset {
    Texture *data;
    bool persist;
};

struct SpriteAsset {
    Sprite *data;
    bool persist;
};

struct MusicAsset {
    Music *data;
    bool persist;
};

struct SoundAsset {
    Sound *data;
    bool persist;
};

struct ImageAsset {
    Image data;
    bool persist;
};

struct FontAsset {
    Font *data;
    bool persist;
};

struct TextAsset {
    Text *data;
    bool persist;
};

struct RectangleShapeAsset {
    RectangleShape *data;
    bool persist;
};

// Render
typedef sf::View Camera;
typedef sf::FloatRect FloatRect;
typedef sf::Event Event;

// Events
typedef sf::Keyboard Keyboard;
typedef sf::Mouse Mouse;
typedef sf::Joystick Joystick;



// PROFILER
const bool SHOW_PROFILER_INFO             = true;
#define ProfileInit() time_t _ME_profile_ = 0;
#define ProfileStart() _ME_profile_       = ME::Profiler::profileStart();
#define ProfileEnd(x) ME::Profiler::profileEnd(x, _ME_profile_);

struct windowInformation{
    int width;
    int height;
    int bitsPerPixel;
    bool fullScreen;
    std::string windowName;
    windowInformation() {
        width        = ENGINE_DEFAULTS::WIDTH_WINDOW;
        height       = ENGINE_DEFAULTS::HEIGHT_WINDOW;
        bitsPerPixel = ENGINE_DEFAULTS::BITS_PER_PIXEL_WINDOW;
        fullScreen   = ENGINE_DEFAULTS::FULLSCREEN_WINDOW;
        windowName   = ENGINE_DEFAULTS::ENGINE_NAME;
    }
    windowInformation(int w, int h, int b, bool f, std::string name) {
        width        = w;
        height       = h;
        bitsPerPixel = b;
        fullScreen   = f;
        windowName   = name;
    }
};

// Default Types

struct Coord{
    int x;
    int y;
};

// Map
enum TileType { SOLID , EVENT , NORMAL  };

struct TileSize{
    int width;
    int height;
};

struct Tile{
    int id;
    int layer;
    char textureName[300];
    Coord pos;
    TileSize size;
    TileType type;
    float rotate;
    float scale;
    char eventScript[300];
};

struct MapFile{
    char mapName[300];
    int numberTile;
    Tile tiles[10000];
};



// Remove Warning of UNSED function
#ifdef __GNUC__
#define ENGINE_UNUSED __attribute__ ((unused))
#else
#define ENGINE_UNUSED
#endif

#ifndef nullptr
#define nullptr 0
#endif

}

#endif // ENGINE_CONFIG_H
