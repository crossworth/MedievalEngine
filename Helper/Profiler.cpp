#include "Profiler.h"

using namespace ME;

Profiler::Profiler() {
}


time_t Profiler::profileStart() {
    return time(0);
}

void Profiler::profileEnd(std::string what, time_t& timeProfile) {
    if (SHOW_PROFILER_INFO) {
        LOG << ("[Profiler::profileEnd] " + what +
                " duration: " + Data2::int_to_str(time(0) - timeProfile) +
                " seconds").c_str() << std::endl;
    }
    timeProfile = NULL;
}
