#ifndef LUAAPI_H
#define LUAAPI_H
#include <thread>
#include <chrono>
#include <mutex>

#include "LogInc.h"
#include "sol.hpp"
#include "Helper/String.h"
#include "Lua/LuaExportAPI.h"

namespace ME {

class LuaAPI {
public:
    static void loadLibs();
    static void script(const std::string& code);
    static sol::state state;
    
private:
	static bool mInitialized;
	static std::mutex mLock;
    LuaAPI();
    static void do_script(const std::string& code);
};

}

#endif // LUAAPI_H
