#include "LuaAPI.h"

using namespace ME;

sol::state LuaAPI::state;

std::thread LuaAPI::mScriptThread;
std::mutex LuaAPI::mScritpThreadLock;

bool LuaAPI::mInitialized = false;

LuaAPI::LuaAPI() {

}

void LuaAPI::unloadFunctions(const std::vector<std::string> &functions) {
    LuaAPI::mInitialized = false;
    // LuaAPI::state.lua_force_close();
    // return;

    std::string unload_command = "";
    // we have to make a copy here be able to create our iterator
    // C++ const stuff...
    std::vector<std::string> functionsCopy = functions;

    std::vector<std::string>::iterator it = functionsCopy.begin();
    for(; it != functionsCopy.end(); it++) {
        unload_command += *it + " = nil ";
    }

    // NOTE(Pedro): We have to call directly here because we dont want to rang 
    // on LuaAPI::scriptSync if some loop is running
    try {
        LuaAPI::state.script(unload_command);
    } catch(sol::error &err) {
        LOG << Log::LUA_WARNING << err.what() << std::endl;
    }
}

void LuaAPI::loadLibs() {
    try {
        LuaAPI::state.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table, sol::lib::math, sol::lib::bit32, sol::lib::package, sol::lib::coroutine);

        std::string packagePathCode = "package.path = \"" + ENGINE_DEFAULTS::SCRIPTS_PATH + "?.lua\"";

        // NOTE(Pedro): Again, since we are setting the path we have to call this directly
        // otherwise it will hang and give tons of errors
        // sync vs async madness
        try {
            LuaAPI::state.script(packagePathCode);
        } catch(sol::error &err) {
            LOG << Log::LUA_WARNING << err.what() << std::endl;
        }

        // print text with no debug level (clean print)
        LuaAPI::state.set_function("print_text", [](const std::string &message) {
            LOG << message << std::endl;
        });
        LuaExportAPI::exports("print_text", "string", "void", LuaExportType::FUNCTION, "abstract print string to console");

        // inject a custom lua print table function verbose and non verbose
        LuaAPI::state.script("function print_table_verbose (tbl, indent) if not indent then indent = 0 end for k, v in pairs(tbl) do formatting = string.rep(\"  \", indent) .. k .. \": \" if type(v) == \"table\" then log(formatting) print_table_verbose(v, indent+1) elseif type(v) == 'boolean' then log(formatting .. tostring(v)) else log(formatting .. v) end end end");
        LuaExportAPI::exports("print_table_verbose", "table[, int]", "void", LuaExportType::FUNCTION, "print a lua table on console with verbose mode, second argument control if it should have indentation or not, pass a int as the indentation number");

        // non-verbose print_table (clean print)
        LuaAPI::state.script("function print_table (tbl, indent) if not indent then indent = 0 end for k, v in pairs(tbl) do formatting = string.rep(\"  \", indent) .. k .. \": \" if type(v) == \"table\" then print_text(formatting) print_table(v, indent+1) elseif type(v) == 'boolean' then print_text(formatting .. tostring(v)) else print_text(formatting .. v) end end end");
        LuaExportAPI::exports("print_table", "table[, int]", "void", LuaExportType::FUNCTION, "print a lua table on console, second argument control if it should have indentation or not, pass a int as the indentation number");


        LuaAPI::state.set_function("log_v", [](const std::string &message) {
            LOG << Log::LUA_VERBOSE << message << std::endl;
        });
        LuaExportAPI::exports("log_v", "string", "void", LuaExportType::FUNCTION, "log a verbose message to console");

        LuaAPI::state.set_function("log_w", [](const std::string &message) {
            LOG << Log::LUA_WARNING << message << std::endl;
        });
        LuaExportAPI::exports("log_w", "string", "void", LuaExportType::FUNCTION, "log a warning message to console");

        LuaAPI::state.set_function("log_c", [](const std::string &message) {
            LOG << Log::LUA_CRITICAL << message << std::endl;
        });
        LuaExportAPI::exports("log_c", "string", "void", LuaExportType::FUNCTION, "log a critical message to console,");

        // override the print function
        LuaAPI::state.script("function print(something) if (type(something) == \"table\") then print_table(something) else print_text(tostring(something)) end end");
        LuaExportAPI::exports("print", "", "void", LuaExportType::FUNCTION, "print a value on console, argument could be table, variable, string, bool, integer, float");

        // inject a custom function to log all the data types
        LuaAPI::state.script("function log(something) if (type(something) == \"table\") then print_table_verbose(something) else log_v(tostring(something)) end end");
        LuaExportAPI::exports("log", "mixed", "void", LuaExportType::FUNCTION, "log a value on console, argument could be table, variable, string, bool, integer, float");

        LuaAPI::state.set_function("register_function", [](const std::string &name) {
            LuaExportAPI::exports(name, "", "", LuaExportType::FUNCTION, "LuaAPI definied function");
        });
        LuaExportAPI::exports("register_function", "string", "void", LuaExportType::FUNCTION, "register an function on the LuaExportAPI for the console Prediction list, pass the function name as argument");

        LuaAPI::mInitialized = true;
    } catch(sol::error& err) {
        LOG << Log::LUA_WARNING << err.what() << std::endl;
    }
}

void LuaAPI::scriptSync(const std::string &code) {
    if (!LuaAPI::mInitialized) {
        return;
    }

    try {
        LuaAPI::state.script(code);
    } catch(sol::error &err) {
        LOG << Log::LUA_WARNING << err.what() << std::endl;
    }
}

void LuaAPI::scriptASync(const std::string &code) {

    if (!LuaAPI::mInitialized) {
        return;
    }

    LuaAPI::scriptSync(code);
    return;
    mScritpThreadLock.lock();
    mScriptThread = std::thread([code] () {
        try {
            sol::thread runner = sol::thread::create(LuaAPI::state.lua_state());
            runner.state().script(code);
        } catch(sol::error &err) {
            LOG << Log::LUA_WARNING << err.what() << std::endl;
        }
    });

    mScriptThread.detach();
    mScritpThreadLock.unlock();
}

bool LuaAPI::executeScriptASync(const std::string &fileName) {
    if (!LuaAPI::mInitialized) {
        return false;
    }

    std::string code = Script::load(fileName);

    if (code != "") {
        LuaAPI::scriptASync(code);
        return true;
    }

    return false;
}


bool LuaAPI::executeScriptSync(const std::string &fileName) {
    if (!LuaAPI::mInitialized) {
        return false;
    }

    std::string code = Script::load(fileName);

    if (code != "") {
        try {
            LuaAPI::scriptSync(code);
            return true;
        } catch(sol::error &err) {
            LOG << Log::LUA_WARNING << err.what() << std::endl;
        }
    }

    return false;
}
