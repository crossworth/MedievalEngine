#ifndef LUA_H
#define LUA_H
#include "debugger.h"
#include "TO.h"
#include "config.h"

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

namespace ME{

class LuaEngine
{
public:
    static LuaEngine* getInstace();
    void registerFunction(const std::string &name, int (*func)(lua_State *l));
    ~LuaEngine();
    void doFile(const std::string &fileName);
    static bool assertValue(lua_State *l, int argumentsNeed, const char *functionName);
private:
    lua_State* L;
    LuaEngine();
};

}

#endif // LUA_H
