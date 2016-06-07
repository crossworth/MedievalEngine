#ifndef OS_H
#define OS_H
#include <iostream>

#ifdef _WIN32
	#define _OS_WIN
	#define _OS_ "Windows"
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
        #define _OS_IOS_SIMULATOR
		#define _OS_ "iOS Simulator"
    #elif TARGET_OS_IPHONE
        #define _OS_IOS_DEVICE
		#define _OS_ "iOS Device"
    #elif TARGET_OS_MAC
        #define _OS_MAC
		#define _OS_ "MacOS"
    #endif
#elif __ANDROID__
	#define _OS_ANDROID
	#define _OS_ "Android"
#elif __linux__
    #define _OS_LINUX
	#define _OS_ "Linux"
#elif __unix__ // all unices not caught above
	#define _OS_UNIX
    #define _OS_ "Unix"
#endif

#if _WIN32 || _WIN64
	#if _WIN64
		#define ENVIRONMENT64
	#else
		#define ENVIRONMENT32
	#endif
#endif

#if __GNUC__
	#if __x86_64__ || __ppc64__
		#define ENVIRONMENT64
	#else
		#define ENVIRONMENT32
	#endif
#endif


namespace ME {

class OS {
public:
	static std::string getOperationSytemName();
	static bool isWindows();
	static bool isLinux();
	static bool isMacOS();
	static bool isUnix();
	static bool isiOS();
	static bool isAndroid();

	static bool is32Bits();
	static bool is64Bits();


	static std::string NEW_LINE;
	// TODO(Pedro): get language, time, and that kind of stuff
};

}


#endif // OS_H