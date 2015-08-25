#include "Log.h"

using namespace ME;

Log* Log::getInstance(const bool& logToFile,
                      const std::string& fileName,
                      const bool& logTime) {

    static Log* m_instance = new Log(logToFile, fileName, logTime);

    return m_instance;
}


Log::Log(const bool& logToFile,
         const std::string& fileName,
         const bool& logTime) : m_coutStream(std::cout) {

    if (logToFile) {
        m_ofStream.open(fileName.c_str(), std::ios_base::app);
        m_outStream = &m_ofStream;
    } else {
        m_outStream = &m_coutStream;
    }

    *m_outStream << std::endl;
    *m_outStream << "------------------------------------------";
    *m_outStream << std::endl;

    if (logTime) {
        *m_outStream << getTime();
    }
}

std::string Log::getTime() {
    time_t time            = std::time(0);
    std::string timeString = std::ctime(&time);

    return timeString;
}

