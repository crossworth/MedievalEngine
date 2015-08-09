#include "luaengine.h"

using namespace ME;

LuaEngine* LuaEngine::getInstace() {
    static LuaEngine* instace = new LuaEngine();
    return instace;
}

LuaEngine::LuaEngine() {
    L = luaL_newstate();
    luaL_openlibs(L);
}

void LuaEngine::doFile(const std::string &fileName) {
    Debugger *dbg = Debugger::getInstance();
    try {
        if(luaL_dofile(L, fileName.c_str()) == 1) {
            dbg->log(WARNING, 1, ("[LuaEngine::doFile] " + std::string(lua_tostring(L, -1))).c_str());
        }
    } catch (std::exception &e) {
         luaL_error(L, e.what());

         dbg->log(WARNING, 1, ("[LuaEngine::doFile] Exception from Lua (" + std::string(e.what()) + ", " + fileName + ")").c_str());
    }
}

void LuaEngine::registerFunction(const std::string &name, int (*func)(lua_State *l)) {
    lua_register(L, name.c_str(), func);
}

bool LuaEngine::assertValue(lua_State *l, int argumentsNeed, const char *functionName) {
    Debugger *dbg = Debugger::getInstance();

    for (int i = 1; i <= argumentsNeed; i++) {
        if (lua_isnoneornil(l, argumentsNeed)) {
            dbg->log(VERBOSE, 1, ("[LuaEngine::assertValue] Erro with argument " + TO::int_to_str(i) + " on [LuaScript::" + std::string(functionName) + "]").c_str());
            return false;
        }
    }
    return true;
}

LuaEngine::~LuaEngine() {
    lua_close(L);
}

