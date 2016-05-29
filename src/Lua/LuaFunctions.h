#ifndef LUAFUNCTIONS_H
#define LUAFUNCTIONS_H
#include <string>
#include <vector>
#include <algorithm>


namespace ME {

// TODO(pedro): better autocomplete, with the start of the string, and not what the string contain's
class LuaFunctions {
public:

    static void store(const std::string& name);
    // change name of this to something better
    static std::string autoComplete(const std::string& name);
private:
    static std::vector<std::string> mFunctions;

};

}

#endif // LUAFUNCTIONS_H
