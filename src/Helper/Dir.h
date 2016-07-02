#ifndef DIR_H
#define DIR_H
#include <string>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cerrno>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef __WIN32
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
    static bool exists(const std::string& dirPath);
};

}

#endif // DIR_H
