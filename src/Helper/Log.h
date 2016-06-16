#ifndef LOG_H
#define LOG_H
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include "Helper/String.h"
#include "Helper/OS.h"


namespace ME {


class LogObserver {
public:
    virtual void addMessage(const String& message) = 0;
};

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

    inline std::string lock() {
        // lock our resources to avoid crash from thread's related stuff
        mLock.lock();
        return "";
    }

    inline Log& operator<<(std::ostream&(f)(std::ostream&)) {
        // little cheat to get the right enconding
        // we create a wstring and than convert to a utf8string
        // this way we can use on SFML and on console without problems
        *mOutstream << String::wstring_to_UTF8(String::string_to_wstring(mTempOutstream.str())) + OS::NEW_LINE;

        if (mCallOnUpdate != nullptr) {
            mCallOnUpdate->addMessage(String(mTempOutstream.str() + OS::NEW_LINE));
        }

        mTempOutstream.str("");

        mLock.unlock();

        return *this;
    }

    static std::string getTime();

    void setObserver(LogObserver* observer);
    void removeObserver();

    ~Log();
private:
    std::mutex mLock;

    bool mLogToFile;
    std::stringstream mTempOutstream;
    std::ostream* mOutstream;
    std::ostream& mCout;
    std::ofstream mOfstream;
    LogObserver* mCallOnUpdate;
};

}

#endif // LOG_H
