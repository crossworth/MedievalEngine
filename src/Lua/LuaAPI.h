#ifndef MEDIEVALENGINE_LUA_LUAAPI_H_
#define MEDIEVALENGINE_LUA_LUAAPI_H_
#include <thread>
#include <mutex>

#include "LogInc.h"
#include "sol.hpp"

#include "Resources/Script.h"

#include "Helper/String.h"

#include "Lua/LuaExportAPI.h"

namespace ME {

class LuaAPI {
public:
    static void loadLibs();

    static void unloadFunctions(std::vector<std::string> &functions);

    static void script(const std::string &code);
    static bool executeScript(const std::string &fileName);
    static sol::state state;
private:
	static bool mInitialized;
	static std::thread mScriptThread;
	static std::mutex mScritpThreadLock;
    LuaAPI();
};

}

#endif // MEDIEVALENGINE_LUA_LUAAPI_H_
