#include "Profiler.h"

using namespace ME;

Profiler::Profiler() {
}


time_t Profiler::profileStart() {
    return time(0);
}

void Profiler::profileEnd(std::string what, time_t &timeProfile) {
    Debugger *dbg = Debugger::getInstance();

    if ( SHOW_PROFILER_INFO ) {
        dbg->log(VERBOSE, 1, ("[Profiler::profileEnd] " + what + " duration: " + TO::int_to_str(time(0) - timeProfile) + " seconds").c_str());
    }
    timeProfile = NULL;
}
