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
    enum LOG_TYPE {VERBOSE, LUA_VERBOSE, WARNING,
                   LUA_WARNING, CRITICAL, LUA_CRITICAL};
private:
    Log(const bool& logToFile,
        const std::string& fileName,
        const bool& logTime);

    static Log* mInstance;

public:
    static Log* getInstance(const bool& logToFile = false,
                            const std::string& fileName = "output.log",
                            const bool& logTime = false);

    inline Log& operator<<(const char* message) {
        *outStream << std::string(message);
        return *this;
    }

    inline Log& operator<<(const int& number) {
        std::stringstream ss;
        ss << number;
        *outStream << ss.str();
        return *this;
    }

    inline Log& operator<<(const unsigned int& number) {
        std::stringstream ss;
        ss << number;
        *outStream << ss.str();
        return *this;
    }

    inline Log& operator<<(const float& number) {
        std::stringstream ss;
        ss << number;
        *outStream << ss.str();
        return *this;
    }

    inline Log& operator<<(const double& number) {
        std::stringstream ss;
        ss << number;
        *outStream << ss.str();
        return *this;
    }

    inline Log& operator<<(const bool& boolean) {
        if(boolean) {
            *outStream << "true";
        } else {
            *outStream << "false";
        }

        return *this;
    }

    inline Log& operator<<(const LOG_TYPE& type) {
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

    inline Log& operator<<(std::ostream&(*f)(std::ostream&)) {
        *outStream << std::endl;
        return *this;
    }
private:
    std::string getTime();
    std::ostream* outStream;
    std::ostream& mCoutStream;
    std::ofstream mOfStream;
};

}

#endif // LOG_H
