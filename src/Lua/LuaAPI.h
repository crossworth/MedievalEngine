#ifndef MEDIEVALENGINE_LUA_LUAAPI_H_
#define MEDIEVALENGINE_LUA_LUAAPI_H_
#include <thread>
#include <mutex>

#include "LogInc.h"
#include "sol.hpp"

#include "Resources/Script.h"

#include "Helper/String.h"

#include "Lua/LuaExportAPI.h"

// NOTE(Pedro): We make sure we load all libs and set 
// everything right from the start
#define LuaAPIInit() ME::LuaAPI::loadLibs()

namespace ME {

class LuaAPI {
public:
    static void loadLibs();

    static void unloadFunctions(const std::vector<std::string> &functions);

    static void scriptASync(const std::string &code);
    static void scriptSync(const std::string &code);
    static bool executeScriptASync(const std::string &fileName);
    static bool executeScriptSync(const std::string &fileName);

    static sol::state state;
private:
	static bool mInitialized;
	static std::thread mScriptThread;
	static std::mutex mScritpThreadLock;
    LuaAPI();
};

}

#endif // MEDIEVALENGINE_LUA_LUAAPI_H_
