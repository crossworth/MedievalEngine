#include "OS.h"

using namespace ME;

#ifdef _OS_WIN
std::string OS::NEW_LINE = "\r\n";
#else
std::string OS::NEW_LINE = "\n";
#endif

std::string OS::getOperationSytemName() {
	return std::string(_OS_);
}

bool OS::isWindows() {
	#ifdef _OS_WIN
	return true;
	#else
	return false;
	#endif
}

bool OS::isLinux() {
	#ifdef _OS_LINUX
	return true;
	#else
	return false;
	#endif
}

bool OS::isMacOS() {
	#ifdef _OS_MAC
	return true;
	#else
	return false;
	#endif
}

bool isUnix() {
	#ifdef _OS_UNIX
	return true;
	#else
	return false;
	#endif
}

bool isiOS() {
	#if defined(_OS_IOS_SIMULATOR) || defined(TARGET_OS_IPHONE)
	return true;
	#else
	return false;
	#endif
}

bool isAndroid() {
	#ifdef _OS_ANDROID
	return true;
	#else
	return false;
	#endif
}

bool OS::is32Bits() { 
	#ifdef ENVIRONMENT32
	return true;
	#else
	return false;
	#endif
}

bool OS::is64Bits() {
	#ifdef ENVIRONMENT64
	return true;
	#else
	return false;
	#endif
}