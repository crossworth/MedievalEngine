#include "lua.h"

using namespace ME;

Lua* Lua::getInstace(){
    static Lua* instace = new Lua();
    return instace;
}


void Lua::init(){

}

Lua::Lua()
{
    open = true;
    L = luaL_newstate();
    // load Lua libraries
    luaL_openlibs(L);
}
void Lua::doFile(const std::string &fileName){
    try{
        luaL_dofile(L, fileName.c_str());
    }catch (std::exception & e)
    {
         luaL_error(L, e.what());
         Debugger *dbg = Debugger::getInstance();
         dbg->log(WARNING,1,("Exception from lua:" + std::string(e.what())).c_str());
    }
}


void Lua::registerFunction(const std::string &name, int (*func)(lua_State *l)){
    lua_register(L,name.c_str(),func);
}

bool Lua::assertValue(lua_State *l,int n,const char *f){
    Debugger *dbg = Debugger::getInstance();
    for (int i=1; i <= n;i++){
        if ( lua_isnoneornil(l,n)) {
            dbg->log(WARNING,1,("Argumento(" + Converter::int_to_str(i) + ") invalido na funcao " + std::string(f)).c_str());
            return false;
        }
    }
    return true;
}


Lua::~Lua(){
    lua_close(L);
}

