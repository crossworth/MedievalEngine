#ifndef WINDOWINFO_H
#define WINDOWINFO_H
#include "Config.h"

namespace ME {

class WindowInfo {
public:

    WindowInfo();
    WindowInfo(
        int width,
        int height,
        int bitsPerPixel,
       bool fullScreen, 
       std::string name,
       int frameLimit = ENGINE_DEFAULTS::FRAME_LIMIT, 
       bool vsync = ENGINE_DEFAULTS::VSYNC
   );

    int width;
    int height;
    int bitsPerPixel;
    int frameLimit;
    bool vsync;
    bool fullScreen;
    std::string windowName;
};

}

#endif // WINDOWINFO_H