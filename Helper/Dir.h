#ifndef DIR_H
#define DIR_H
#include <string>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cerrno>

#ifdef WINDOWS
    #include <direct.h>
    #define _GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define _GetCurrentDir getcwd
 #endif


namespace ME {

class Dir {
public:
    static std::string getCurrentPath();
private:
    Dir();
};

}

#endif // DIR_H
