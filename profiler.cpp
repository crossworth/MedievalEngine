#include "profiler.h"

using namespace ME;

Profiler::Profiler()
{
}


time_t Profiler::profileStart(){
    return time(0);
}

void Profiler::profileEnd(const std::string & name, time_t &timeProfile){
    Debugger *dbg = Debugger::getInstance();
    if ( ShowProfilerDebug ){
        dbg->log(WARNING,1,("Profiler:" + name + " Duration: " + Converter::int_to_str(time(0) - timeProfile) + " seconds").c_str());
     }
    timeProfile = NULL;
}
