#include "Profiler.h"

using namespace ME;

Profiler::Profiler() {
}


time_t Profiler::profileStart() {
    return time(0);
}

void Profiler::profileEnd(std::string what, time_t& timeProfile) {
    if (SHOW_PROFILER_INFO) {
        LOG << "[Profiler::profileEnd] " + what 
            << " duration: " + Kit::int_str(static_cast<int>(time(0)) - static_cast<int>(timeProfile))
            << " seconds" << std::endl;
    }
    timeProfile = NULL;
}
