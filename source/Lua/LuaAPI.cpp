#include "LuaAPI.h"

using namespace ME;

sol::state LuaAPI::state;

LuaAPI::LuaAPI() {

}

void LuaAPI::loadLibs() {
    try {
        LuaAPI::state.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table);

        // inject a custom lua print table function
        LuaAPI::script("function print_table (tbl, indent) if not indent then indent = 0 end for k, v in pairs(tbl) do formatting = string.rep(\"  \", indent) .. k .. \": \" if type(v) == \"table\" then print(formatting) print_table(v, indent+1) elseif type(v) == 'boolean' then log(formatting .. tostring(v)) else log(formatting .. v) end end end");
        LuaFunctions::store("print_table");

        //TODO(pedro): override this function to accept all the types
        // including tables
        // make a lua function and inject like the lua_print table function
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

        LuaAPI::state.set_function("register_function", [](const std::string& name){
            LuaFunctions::store(name);
        });
        LuaFunctions::store("register_function");

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
