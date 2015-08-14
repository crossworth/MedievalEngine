#include "Dir.h"

using namespace ME;

std::string Dir::getCurrentPath() {
    char cCurrentPath[FILENAME_MAX];

    _GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));

    assert(errno == 0);
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
    return std::string(cCurrentPath);
}

Dir::Dir() {

}

