#ifndef LUAAPI_H
#define LUAAPI_H
#include "LogInc.h"
#include "sol.hpp"


namespace ME {

class LuaAPI {
public:
    LuaAPI();
    static void script(const std::string& code);
    static sol::state state;

private:
    static void luaLog(const std::string& message, const std::string& type = "verbose");
};

}

#endif // LUAAPI_H
