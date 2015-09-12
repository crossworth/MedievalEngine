#include "Config.h"
#include "Helper/Log.h"



#ifndef LOG_OBJECT
#define LOG_OBJECT ME::Log::getInstance(ME::_LOG_WRITE_TO_FILE, ME::_LOG_FILE_NAME)
#endif

#ifndef LOG
#define LOG (*LOG_OBJECT) << (*LOG_OBJECT).lock() << ME::Log::getTime()
#endif


