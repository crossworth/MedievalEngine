#ifndef LUAEXPOSE_H
#define LUAEXPOSE_H
#include "Lua/LuaAPI.h"

namespace ME {

/**
 * LuaExpose
 * Expose the Lua Functions from one class to
 */
class LuaExpose {
protected:
    virtual void exposeLuaAPI() = 0;
};

}

#endif // LUAEXPOSE_H
