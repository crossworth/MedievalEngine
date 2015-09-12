#include "LuaAPI.h"

using namespace ME;

sol::state LuaAPI::state;

LuaAPI::LuaAPI() {

}

void LuaAPI::loadLibs() {
    try {
        LuaAPI::state.open_libraries(sol::lib::base);

        LuaAPI::state.set_function("log", [](const std::string& message){
            LOG << Log::LUA_VERBOSE << message << std::endl;
        });
        LuaFunctions::store("log");

        LuaAPI::state.set_function("log_w", [](const std::string& message){
            LOG << Log::LUA_WARNING << message << std::endl;
        });
        LuaFunctions::store("log_w");


        LuaAPI::state.set_function("log_c", [](const std::string& message){
            LOG << Log::LUA_CRITICAL << message << std::endl;
        });
        LuaFunctions::store("log_c");

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

