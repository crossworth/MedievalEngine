#ifndef PROFILER_H
#define PROFILER_H
#include <ctime>
#include <iostream>
#include <string>
#include <LogInc.h>
#include <Helper/Data2.h>


namespace ME {

const bool SHOW_PROFILER_INFO             = true;
#define ProfileInit() time_t _ME_profile_ = 0;
#define ProfileStart() _ME_profile_       = ME::Profiler::profileStart(); LOG << "[Profiler::profileStart] Profiler started" << std::endl;
#define ProfileEnd(x) ME::Profiler::profileEnd(x, _ME_profile_);

class Profiler {
public:
    static time_t profileStart();
    static void profileEnd(std::string what, time_t& timeProfile);
private:
    Profiler();
};

}

#endif // PROFILER_H
