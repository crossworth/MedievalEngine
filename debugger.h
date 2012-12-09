#ifndef DEBUGGER_H
#define DEBUGGER_H
#include "engine_config.h"
#include <stdarg.h>

namespace ME{

class Debugger
{
public:
    static Debugger * getInstance();
    void log(const debug_type &type,int numArgs,...);
    ~Debugger();
private:
    std::string fileName;
    bool debugToFile;
    bool enableDebug;
    std::ofstream mFile;
    Debugger();
    void write_to_file(char * str);
};

}

#endif // DEBUGGER_H
