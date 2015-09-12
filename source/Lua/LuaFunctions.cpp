#include "LuaFunctions.h"

using namespace ME;

std::vector<std::string> LuaFunctions::mFunctions;

void LuaFunctions::store(const std::string& name) {
    LuaFunctions::mFunctions.push_back(name);
}

std::string LuaFunctions::getTypeHint(const std::string& name) {
    // we only with functions with more than 2 chars
    if (name.length() < 3) {
        return "";
    }


    // create static variables to hold information to speed things up
    // options hold our options for a determined word
    static std::vector<std::string> options;
    // holds the last index acessed
    static int lastIndex          = 0;
    // holds the max number of index, -1 when node found
    static int maxIndex           = -1;
    // hold the name of our previus search
    static std::string lastSearch = "";


    // compare if we already search the functions array for the name
    if (lastSearch != name) {
        // if not we clear ti
        options.clear();

        // create some iterators
        auto it  = LuaFunctions::mFunctions.begin();
        auto end = LuaFunctions::mFunctions.end();

        // serach for possibles functions
        for(; it != end; it++) {
            if ((*it).find(name) != std::string::npos) {
                options.push_back((*it));
            }
        }
        
        // if we found something
        if (options.size() > 0) {
            // sort it to get better results
            std::sort(options.begin(), options.end());

            // set the max index
            maxIndex = static_cast<int>(options.size());
        } else {
            // otherwise we just set the max index
            maxIndex  = -1;
        }

        // and reset the last index
        lastIndex  = 0;
        lastSearch = name;
    } 

    // if we have itens on the array
    if (maxIndex != -1) {
        // loop back to start
        if (lastIndex >= maxIndex) {
            lastIndex = 0;
        }
        // return and incremment
        return options[lastIndex++];
    } else {
        // return nothing
        return "";
    }
}

