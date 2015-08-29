#include "Config.h"
#include "Helper/Log.h"

#ifndef LOG_CLEAN
#ifdef LOG_FILE_NUMBERS
#define LOG_CLEAN *ME::Log::getInstance(ME::_LOG_WRITE_TO_FILE, ME::_LOG_FILE_NAME) << __FILE__ << ":" << __LINE__ << " "
#else
#define LOG_CLEAN *ME::Log::getInstance(ME::_LOG_WRITE_TO_FILE, ME::_LOG_FILE_NAME)
#endif
#endif

#ifndef LOG
#define LOG LOG_CLEAN << ME::Log::getTime()
#endif
