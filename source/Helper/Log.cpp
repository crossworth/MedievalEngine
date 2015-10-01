#include "Log.h"

using namespace ME;

Log* Log::getInstance(const bool& logToFile, const std::string& fileName) {
    static Log* mInstance = new Log(logToFile, fileName);
    return mInstance;
}

Log::Log(const bool& logToFile, const std::string& fileName) : mCout(std::cout) {
    mLogToFile = logToFile;
    if (mLogToFile) {
        mOfstream.open(fileName.c_str(), std::ios_base::app);
        mOutstream = &mOfstream;
    } else {
        mOutstream = &mCout;
    }

    mCallOnUpdate = nullptr;

    mTempOutstream << std::endl;
    mTempOutstream << "------------------------------------------";
    mTempOutstream << std::endl;
}

std::string Log::getTime() {
    time_t time  = std::time(0);
    tm* timeInfo = localtime(&time);

    char buffer[80];

    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", timeInfo);

    std::string timeString(buffer);
    return std::string(timeString + " ");
}

Log::~Log() {
    if (mLogToFile) {
        mOfstream.close();
    }
}


void Log::setObserver(LogObserver* observer) {
    mCallOnUpdate = observer;
}
