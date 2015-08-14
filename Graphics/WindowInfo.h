#ifndef WINDOWINFO_H
#define WINDOWINFO_H
#include <iostream>
#include <Config.h>

namespace ME {

class WindowInfo {
public:

    WindowInfo();

    WindowInfo(int w, int h, int b, bool f, std::string name);

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
