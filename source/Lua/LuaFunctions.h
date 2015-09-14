#ifndef LUAFUNCTIONS_H
#define LUAFUNCTIONS_H
#include <string>
#include <vector>
#include <algorithm>


namespace ME {

// TODO(pedro): better parser for autocomplete, 
// make possible to autocomplete after spaces, inside functions names, and stuff
// like print_table(window_get_position) 
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