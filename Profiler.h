#ifndef PROFILER_H
#define PROFILER_H
#include "Config.h"
#include <time.h>
#include "Debugger.h"
#include "TO.h"


namespace ME {

class Profiler {
public:
    static time_t profileStart();
    static void profileEnd(std::string what, time_t &timeProfile);
private:
    Profiler();
};

}

#endif // PROFILER_H
