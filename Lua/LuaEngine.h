//#ifndef LUA_H
//#define LUA_H
//#include "Log.h"
//#include "TO.h"
//#include "Config.h"

//extern "C" {
//    #include <lua.h>
//    #include <lualib.h>
//    #include <lauxlib.h>
//}

//namespace ME {

//class LuaEngine {
//public:
//    static LuaEngine* getInstace();
//    void registerFunction(const std::string &name, int (*func)(lua_State *l));
//    ~LuaEngine();
//    void doFile(const std::string &fileName);
//    static bool assertValue(lua_State *l, int argumentsNeed, const char *functionName);
//    void callFunction(const std::string &funcName, const std::string &data1, const std::string &data2);
//    void callRegistredFunction(const std::string &funcName);
//private:
//    lua_State* L;
//    LuaEngine();
//    static LuaEngine* instance;
//};

//}

//#endif // LUA_H
