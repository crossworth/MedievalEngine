#ifndef DEBUGGER_H
#define DEBUGGER_H
#include "Config.h"
#include <stdarg.h>

namespace ME {

class Debugger {
public:
    static Debugger * getInstance();
    void log(const DEBUG_TYPE &type,int numArgs,...);
    ~Debugger();
private:
    std::string fileName;
    bool debugToFile;
    bool enableDebug;
    std::ofstream mFile;
    Debugger();
    static Debugger* dbg;
    void write_to_file(char * str);
};

}

#endif // DEBUGGER_H
