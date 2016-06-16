#ifndef LUAAPI_H
#define LUAAPI_H
#include <thread>

#include "LogInc.h"
#include "sol.hpp"
#include "Helper/String.h"
#include "Lua/LuaExportAPI.h"

namespace ME {

class LuaAPI {
public:
    static void loadLibs();

    static void script(const std::string &code);
    static void scriptSync(const std::string &code);
    static void executeScript(const std::string &fileName);
    static void executeScriptSync(const std::string &fileName);

    static void removeFunctions(const std::vector<std::string> &functions);

    static sol::state state;
private:
	static bool mInitialized;
    LuaAPI();
};

}

#endif // LUAAPI_H
