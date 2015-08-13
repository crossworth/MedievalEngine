#include "LuaEngine.h"

using namespace ME;

LuaEngine* LuaEngine::instance = nullptr;

LuaEngine* LuaEngine::getInstace() {
    if (instance == nullptr) {
        instance = new LuaEngine();
    }
    return instance;
}

LuaEngine::LuaEngine() {
    L = luaL_newstate();
    luaL_openlibs(L);
}

void LuaEngine::callFunction(const std::string &funcName, const std::string &data1, const std::string &data2) {
    lua_getglobal(L, funcName.c_str());

    if(lua_isfunction(L, -1)) {
        lua_pushstring(L, data1.c_str());
        lua_pushstring(L, data2.c_str());
        lua_call(L, 2, 0);
    }
}

void LuaEngine::callRegistredFunction(const std::string &funcName) {
    lua_getglobal(L, funcName.c_str());

    if(lua_isfunction(L, -1)) {
        lua_call(L, 0, 0);
    }
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

