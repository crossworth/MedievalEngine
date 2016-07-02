#ifndef MEDIEVALENGINE_WINDOW_WINDOWINFO_H_
#define MEDIEVALENGINE_WINDOW_WINDOWINFO_H_
#include "Config.h"
#include "Helper/String.h"

namespace ME {

class WindowInfo {
public:

    WindowInfo();
    WindowInfo(
        uint16 width,
        uint16 height,
        uint8 bitsPerPixel,
       bool fullScreen, 
       String name,
       uint16 frameLimit = ENGINE_DEFAULTS::FRAME_LIMIT, 
       bool vsync = ENGINE_DEFAULTS::VSYNC
   );

    uint16 width;
    uint16 height;
    uint8 bitsPerPixel;
    uint16 frameLimit;
    bool vsync;
    bool fullScreen;
    String windowName;
};

}

#endif // MEDIEVALENGINE_WINDOW_WINDOWINFO_H_
