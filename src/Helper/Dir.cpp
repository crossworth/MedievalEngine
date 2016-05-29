#include "Dir.h"

using namespace ME;

std::string Dir::getCurrentPath() {
    char cCurrentPath[FILENAME_MAX];

    _GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));

    assert(errno == 0);
    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
    return std::string(cCurrentPath);
}

bool Dir::exists(const std::string& dirPath) {
	struct stat info;

	if(stat(dirPath.c_str(), &info) == 0 && (info.st_mode & S_IFDIR)) {
	    return true;
	}
	
	return false;
}