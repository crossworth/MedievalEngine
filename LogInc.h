#include <Helper/Log.h>

/**
 * Descomentar a linha abaixo para exibir o nome do arquivo e linha durante o log
 * */
// #define LOG_FILE_NUMBERS

#ifndef LOG
#ifdef LOG_FILE_NUMBERS
#define LOG *ME::Log::getInstance(ME::_LOG_WRITE_TO_FILE, ME::_LOG_FILE_NAME, ME::_LOG_LOG_TIME) << __FILE__ << ":" << __LINE__ << " "
#else
#define LOG *ME::Log::getInstance(ME::_LOG_WRITE_TO_FILE, ME::_LOG_FILE_NAME, ME::_LOG_LOG_TIME)
#endif
#endif
