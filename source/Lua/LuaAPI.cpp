#include "LuaAPI.h"

using namespace ME;

sol::state LuaAPI::state;

LuaAPI::LuaAPI() {
    try {
        LuaAPI::state.open_libraries(sol::lib::base);

        LuaAPI::state.set_function("log", &LuaAPI::luaLog);

    } catch(sol::error& err) {
        LOG << Log::LUA_WARNING << err.what() << std::endl;
    }
}

void LuaAPI::script(const std::string& code) {
    try {
        LuaAPI::state.script(code);
    } catch(sol::error& err) {
        LOG << Log::LUA_WARNING << err.what() << std::endl;
    }
}

void LuaAPI::luaLog(const std::string& message, const std::string& type) {
    if (type == "warning") {
        LOG << Log::LUA_WARNING << message << std::endl;
    } else if(type == "critical") {
        LOG << Log::LUA_CRITICAL << message << std::endl;
    } else {
        LOG << Log::LUA_VERBOSE << message << std::endl;
    }
}
