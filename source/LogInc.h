#include "Config.h"
#include "Helper/Log.h"

#ifndef LOG
#define LOG *ME::Log::getInstance(ME::_LOG_WRITE_TO_FILE, ME::_LOG_FILE_NAME) << ME::Log::getTime()
#endif
