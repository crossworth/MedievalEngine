#ifndef DEBUGGER_H
#define DEBUGGER_H
#include "Config.h"

namespace ME {

enum LogType {VERBOSE, LUA_VERBOSE, WARNING, CRITICAL};

class Log {
public:

    friend std::ostream& operator<< (std::ostream& stream, const std::string &what);
    friend std::ostream& operator<< (std::ostream& stream, const LogType &type);


    // TODO: Overload the endl operator

private:
    Log();
};

}

#endif // DEBUGGER_H
