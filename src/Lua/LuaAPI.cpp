#include "LuaAPI.h"

using namespace ME;

sol::state LuaAPI::state;

LuaAPI::LuaAPI() {

}

void LuaAPI::loadLibs() {
    try {
        LuaAPI::state.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table);


        // print text with no debug level (clean print)
        LuaAPI::state.set_function("print_text", [](const std::string& message){
            LOG << message << std::endl;
        });
        LuaFunctions::store("print_text");


        // inject a custom lua print table function verbose and non verbose
        LuaAPI::script("function print_table_verbose (tbl, indent) if not indent then indent = 0 end for k, v in pairs(tbl) do formatting = string.rep(\"  \", indent) .. k .. \": \" if type(v) == \"table\" then log(formatting) print_table_verbose(v, indent+1) elseif type(v) == 'boolean' then log(formatting .. tostring(v)) else log(formatting .. v) end end end");
        LuaFunctions::store("print_table_verbose");

        // non-verbose print_table (clean print)
        LuaAPI::script("function print_table (tbl, indent) if not indent then indent = 0 end for k, v in pairs(tbl) do formatting = string.rep(\"  \", indent) .. k .. \": \" if type(v) == \"table\" then print_text(formatting) print_table(v, indent+1) elseif type(v) == 'boolean' then print_text(formatting .. tostring(v)) else print_text(formatting .. v) end end end");
        LuaFunctions::store("print_table");


        LuaAPI::state.set_function("log_v", [](const std::string& message){
            LOG << Log::LUA_VERBOSE << message << std::endl;
        });
        LuaFunctions::store("log_v");

        LuaAPI::state.set_function("log_w", [](const std::string& message){
            LOG << Log::LUA_WARNING << message << std::endl;
        });
        LuaFunctions::store("log_w");

        LuaAPI::state.set_function("log_c", [](const std::string& message){
            LOG << Log::LUA_CRITICAL << message << std::endl;
        });
        LuaFunctions::store("log_c");

        // override the print function
        LuaAPI::script("function print(something) if (type(something) == \"table\") then print_table(something) else log_v(tostring(something)) end end");
        LuaFunctions::store("print");

        // inject a custom function to log all the data types
        LuaAPI::script("function log(something) if (type(something) == \"table\") then print_table_verbose(something) else log_v(tostring(something)) end end");
        LuaFunctions::store("log");

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
