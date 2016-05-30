#ifndef LUAAPI_H
#define LUAAPI_H
#include "LogInc.h"
#include "sol.hpp"
#include "Lua/LuaExportAPI.h"


namespace ME {

class LuaAPI {
public:
    static void loadLibs();
    static void script(const std::string& code);
    static sol::state state;
    
private:
    LuaAPI();
};

}

#endif // LUAAPI_H
