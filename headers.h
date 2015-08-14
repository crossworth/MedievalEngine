#ifndef HEADERS_H
#define HEADERS_H
#include <Config.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>

#include <Helper/ID.h>
#include <Helper/Key.h>
#include <Helper/Vect2.h>
#include <Helper/Vect3.h>
#include <Helper/Data2.h>
#include <Helper/Log.h>
#include <Helper/CFGParser.h>
#include <Helper/Dir.h>
#include <Helper/Color.h>

#include <Assets/Asset.h>
#include <Assets/AssetsManager.h>
#include <Assets/Texture.h>

#include <Graphics/Drawable.h>
#include <Graphics/WindowInfo.h>
#include <Graphics/Window.h>


#define LOG *ME::Log::getInstance(ME::_LOG_WRITE_TO_FILE, ME::_LOG_FILE_NAME, ME::_LOG_LOG_TIME)

#define USE_LOG extern ME::Log LOG;

// Remove Warning of UNSED function
#ifdef __GNUC__
#define ENGINE_UNUSED __attribute__ ((unused))
#else
#define ENGINE_UNUSED
#endif

#ifndef nullptr
#define nullptr 0
#endif


#endif // HEADERS_H
