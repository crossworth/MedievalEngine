#include "WindowInfo.h"

using namespace ME;

WindowInfo::WindowInfo(int w, int h, int b, bool f, std::string name) {
    width        = w;
    height       = h;
    bitsPerPixel = b;
    fullScreen   = f;
    windowName   = name;
    frameLimit   = ENGINE_DEFAULTS::FRAME_LIMIT;
    vsync        = ENGINE_DEFAULTS::VSYNC;
}

WindowInfo::WindowInfo() {
    width        = ENGINE_DEFAULTS::WIDTH_WINDOW;
    height       = ENGINE_DEFAULTS::HEIGHT_WINDOW;
    bitsPerPixel = ENGINE_DEFAULTS::BITS_PER_PIXEL_WINDOW;
    fullScreen   = ENGINE_DEFAULTS::FULLSCREEN_WINDOW;
    windowName   = ENGINE_DEFAULTS::ENGINE_NAME;
    frameLimit   = ENGINE_DEFAULTS::FRAME_LIMIT;
    vsync        = ENGINE_DEFAULTS::VSYNC;
}
