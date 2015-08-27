#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>


namespace ME {

class Log {
public:
    enum LogType {VERBOSE, LUA_VERBOSE, WARNING,
                   LUA_WARNING, CRITICAL, LUA_CRITICAL};
private:
    Log(const bool& logToFile,
        const std::string& fileName,
        const bool& logTime);

public:
    static Log* getInstance(const bool& logToFile = false,
                            const std::string& fileName = "output.log",
                            const bool& logTime = false);

    inline Log& operator<<(const char* message) {
        *m_outStream << std::string(message);
        return *this;
    }

    inline Log& operator<<(const std::string& message) {
        *m_outStream << message;
        return *this;
    }

    inline Log& operator<<(const int& number) {
        std::stringstream ss;
        ss << number;
        *m_outStream << ss.str();
        return *this;
    }

    inline Log& operator<<(const unsigned int& number) {
        std::stringstream ss;
        ss << number;
        *m_outStream << ss.str();
        return *this;
    }

    inline Log& operator<<(const float& number) {
        std::stringstream ss;
        ss << number;
        *m_outStream << ss.str();
        return *this;
    }

    inline Log& operator<<(const double& number) {
        std::stringstream ss;
        ss << number;
        *m_outStream << ss.str();
        return *this;
    }

    inline Log& operator<<(const bool& boolean) {
        if(boolean) {
            *m_outStream << "true";
        } else {
            *m_outStream << "false";
        }

        return *this;
    }

    inline Log& operator<<(const LogType& type) {
        switch (type) {
        case VERBOSE:
            *m_outStream << "[VERBOSE] ";
            break;
        case LUA_VERBOSE:
            *m_outStream << "[LUA_VERBOSE] ";
            break;
        case WARNING:
            *m_outStream << "[WARNING] ";
            break;
        case LUA_WARNING:
            *m_outStream << "[LUA_WARNING] ";
            break;
        case CRITICAL:
            *m_outStream << "[CRITICAL] ";
            break;
        case LUA_CRITICAL:
            *m_outStream << "[LUA_CRITICAL] ";
            break;
        default:
            *m_outStream << "[UNKNOWN] ";
            break;
        }
        return *this;
    }

    inline Log& operator<<(std::ostream&(*/*f*/)(std::ostream&)) {
        *m_outStream << std::endl;
        return *this;
    }
    static std::string getTime();
private:
    std::ostream* m_outStream;
    std::ostream& m_coutStream;
    std::ofstream m_ofStream;
};

}

#endif // LOG_H
