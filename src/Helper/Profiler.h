#ifndef PROFILER_H
#define PROFILER_H
#include <SFML/Graphics.hpp>
#include "Helper/Clock.h"
#include "Lua/LuaAPI.h"


#define ProfileBlock() ME::Profiler _me_profiler(__FUNCTION__, "")
#define ProfileBlockStr(x) ME::Profiler _me_profiler(__FUNCTION__, x)

namespace ME {

class MedievalEngine;

class Profiler {
public:
    /**
     * The default Metric system for the profiler
     */
    enum Type {
        SECONDS,      ///< Seconds
        MILLISECONDS, ///< MilliSeconds
        MICROSECONDS  ///< MicroSeconds
    };
public:
    Profiler(const char* functionName, const char* text = "");
    ~Profiler();

    static bool isVisible();
    static void setVisible(bool visible);
    static void printRecords();
    static void printRecords(MedievalEngine* engine);
    static void setOutputType(const Profiler::Type& type);
    static void setUpdateTime(unsigned int time);

    static void exposeLuaAPI();

private:
    static sf::Text mDebugText;
    static unsigned int mUpdateTime;
    static Clock mClockSort;
    static bool mIsLuaExposed;
    static bool mIsVisible;
    static std::map<std::string, MEUInt64> Records;
    static std::map<MEUInt64, std::string> recordsSorted;
    Profiler();
    Clock mClock;
    static Type mType;
    std::string mFunctionName;
};

}

#endif // PROFILER_H
