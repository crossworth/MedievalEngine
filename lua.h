#ifndef LUA_H
#define LUA_H
#include "debugger.h"
#include "converter.h"
#include "engine_config.h"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

namespace ME{

class Lua
{
public:
    static Lua* getInstace();
    void init();
    void registerFunction(const std::string &name, int (*func)(lua_State *l));
    ~Lua();
    void doFile(const std::string &fileName);
    static bool assertValue(lua_State *l,int n,const char *f);
private:
    bool open;
    lua_State* L;
    Lua();
};

}

#endif // LUA_H
