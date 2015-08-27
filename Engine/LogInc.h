#include "Config.h"
#include "Helper/Log.h"


#ifndef LOG_base
#ifdef LOG_FILE_NUMBERS
#define LOG_base *ME::Log::getInstance(ME::_LOG_WRITE_TO_FILE, ME::_LOG_FILE_NAME) << __FILE__ << ":" << __LINE__ << " "
#else
#define LOG_base *ME::Log::getInstance(ME::_LOG_WRITE_TO_FILE, ME::_LOG_FILE_NAME)
#endif
#endif


/**
 * We log the time with a simple macro modification
 * */
#ifndef LOG
#define LOG LOG_base << ME::Log::getTime()
#endif
