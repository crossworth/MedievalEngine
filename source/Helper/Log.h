#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>


namespace ME {
    
// TODO(Pedro): Make this thread safe
class Log {
public:
    /**
     * The LogType enum
     */
    enum LogType {
        VERBOSE,     ///< A verbose log from C++
        LUA_VERBOSE, ///< A verbose log from Lua
        WARNING,     ///< A warning log from C++
        LUA_WARNING, ///< A warning log from Lua
        CRITICAL,    ///< A critical log from C++
        LUA_CRITICAL ///< A critical log from Lua
    };

private:
    Log(const bool& logToFile, const std::string& fileName);
public:
    static Log* getInstance(const bool& logToFile = false, const std::string& fileName = "output.log");

    inline Log& operator<<(const char* message) {
        mTempOutstream << std::string(message);
        return *this;
    }

    inline Log& operator<<(const std::string& message) {
        mTempOutstream << message;
        return *this;
    }

    inline Log& operator<<(const int& number) {
        std::stringstream ss;
        ss << number;
        mTempOutstream << ss.str();
        return *this;
    }

    inline Log& operator<<(const unsigned int& number) {
        std::stringstream ss;
        ss << number;
        mTempOutstream << ss.str();
        return *this;
    }

    inline Log& operator<<(const float& number) {
        std::stringstream ss;
        ss << number;
        mTempOutstream << ss.str();
        return *this;
    }

    inline Log& operator<<(const double& number) {
        std::stringstream ss;
        ss << number;
        mTempOutstream << ss.str();
        return *this;
    }

    inline Log& operator<<(const bool& boolean) {
        if(boolean) {
            mTempOutstream << "true";
        } else {
            mTempOutstream << "false";
        }

        return *this;
    }

    inline Log& operator<<(const LogType& type) {
        switch (type) {
        case VERBOSE:
            mTempOutstream << "[VERBOSE] ";
            break;
        case LUA_VERBOSE:
            mTempOutstream << "[LUA_VERBOSE] ";
            break;
        case WARNING:
            mTempOutstream << "[WARNING] ";
            break;
        case LUA_WARNING:
            mTempOutstream << "[LUA_WARNING] ";
            break;
        case CRITICAL:
            mTempOutstream << "[CRITICAL] ";
            break;
        case LUA_CRITICAL:
            mTempOutstream << "[LUA_CRITICAL] ";
            break;
        default:
            mTempOutstream << "[UNKNOWN] ";
            break;
        }
        return *this;
    }

    inline Log& operator<<(std::ostream&(f)(std::ostream&)) {
        *mOutstream << mTempOutstream.str() + "\n";
        mTempOutstream.str("");
        return *this;
    }
    static std::string getTime();

    ~Log();
private:
    bool mLogToFile;
    std::stringstream mTempOutstream;
    std::ostream* mOutstream;
    std::ostream& mCout;
    std::ofstream mOfstream;
};

}

#endif // LOG_H
