#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <Config.h>

namespace ME {

class Log {
public:
    enum LogType {VERBOSE, LUA_VERBOSE, WARNING, LUA_WARNING, CRITICAL, LUA_CRITICAL};

private:
    Log(const bool &logToFile, const std::string &fileName, const bool &logTime);
    static Log* mInstance;

public:
    static Log* getInstance(const bool &logToFile = false, const std::string &fileName = "output.log", const bool &logTime = false);

    Log &operator<<(const char *message) {
        *outStream << std::string(message);
        return *this;
    }

    Log &operator<<(const int &number) {
        std::stringstream ss;
        ss << number;
        *outStream << ss.str();
        return *this;
    }

    Log &operator<<(const float &number) {
        std::stringstream ss;
        ss << number;
        *outStream << ss.str();
        return *this;
    }

    Log &operator<<(const double &number) {
        std::stringstream ss;
        ss << number;
        *outStream << ss.str();
        return *this;
    }

    Log &operator<<(const bool &boolean) {
        if(boolean) {
            *outStream << "true";
        } else {
            *outStream << "false";
        }

        return *this;
    }

    Log &operator<<(const LogType &type) {
        switch (type) {
        case VERBOSE:
            *outStream << "[VERBOSE] ";
            break;
        case LUA_VERBOSE:
            *outStream << "[LUA_VERBOSE] ";
            break;
        case WARNING:
            *outStream << "[WARNING] ";
            break;
        case LUA_WARNING:
            *outStream << "[LUA_WARNING] ";
            break;
        case CRITICAL:
            *outStream << "[CRITICAL] ";
            break;
        case LUA_CRITICAL:
            *outStream << "[LUA_CRITICAL] ";
            break;
        default:
            *outStream << "[UNKNOWN] ";
            break;
        }
        return *this;
    }

    Log &operator<<(std::ostream&(*f)(std::ostream&)) {
        *outStream << std::endl;
        return *this;
    }

private:
    std::string getTime();

    std::ostream *outStream;
    std::ostream &mCoutStream;
    std::ofstream mOfStream;
};

}

#endif // LOG_H
