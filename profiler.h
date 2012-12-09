#ifndef PROFILER_H
#define PROFILER_H
#include "engine_config.h"
#include "time.h"
#include "debugger.h"
#include "converter.h"


namespace ME{

class Profiler
{
public:
    static time_t profileStart();
    static void profileEnd(const std::string &name, time_t &timeProfile);
private:
    Profiler();
};

}
#endif // PROFILER_H
