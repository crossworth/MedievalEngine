#ifndef LUAFUNCTIONS_H
#define LUAFUNCTIONS_H
#include <string>
#include <vector>
#include <algorithm>


namespace ME {

class LuaFunctions {
public:
    
    static void store(const std::string& name);
    static std::string getTypeHint(const std::string& name);

private:
    static std::vector<std::string> mFunctions;

};

}

#endif // LUAFUNCTIONS_H