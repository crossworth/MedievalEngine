#ifndef MEDIEVALENGINE_LOGINC_H_
#define MEDIEVALENGINE_LOGINC_H_

#include "Config.h"
#include "Helper/Log.h"

namespace ME {
	const bool _LOG_WRITE_TO_FILE    = false;
	const std::string _LOG_FILE_NAME = "output.log";
}

#ifndef LOG_OBJECT
#define LOG_OBJECT ME::Log::getInstance(ME::_LOG_WRITE_TO_FILE, ME::_LOG_FILE_NAME)
#endif

#ifndef LOG
#define LOG (*LOG_OBJECT) << (*LOG_OBJECT).lock() << ME::Log::getTime()
#endif


#endif // MEDIEVALENGINE_LOGINC_H_