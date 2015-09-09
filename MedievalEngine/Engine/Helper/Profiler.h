#ifndef PROFILER_H
#define PROFILER_H
#include <map>
#include <string>
#include <iostream>
#include "Helper/Clock.h"


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
    Profiler(char* functionName, char* text = "");
    ~Profiler();

    static void printRecords();
    static void printRecords(MedievalEngine* engine);
    static void setOutputType(const Profiler::Type& type);
private:
    static std::map<std::string, MEUInt64> Records;
    Profiler();
    Clock mClock;
    static Type mType;
    std::string mFunctionName;
};

}

#endif // PROFILER_H
