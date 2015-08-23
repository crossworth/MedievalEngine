#include "WindowInfo.h"

using namespace ME;

WindowInfo::WindowInfo(int width, int height, int bitsPerPixel, bool fullScreen, std::string name) {
    this->width        = width;
    this->height       = height;
    this->bitsPerPixel = bitsPerPixel;
    this->fullScreen   = fullScreen;
    this->windowName   = name;
    this->frameLimit   = ENGINE_DEFAULTS::FRAME_LIMIT;
    this->vsync        = ENGINE_DEFAULTS::VSYNC;
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
