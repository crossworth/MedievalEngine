#include "LuaExportAPI.h"

using namespace ME;

std::vector<LuaExportObject> LuaExportAPI::mExports;

void LuaExportAPI::exports(const std::string& name, const std::string& args, const std::string& returnType, const LuaExportType& type, const std::string& comments) {
    LuaExportObject tmp;

    tmp.name       = name;
    tmp.args       = args;
    tmp.returnType = returnType;
    tmp.type       = type;
    tmp.comments   = comments;

    LuaExportAPI::mExports.push_back(tmp);
}

bool LuaExportAPI::generateFunctionsList(const std::string& fileName) {
    std::ofstream outFile;

    outFile.open(fileName.c_str(), std::ios::out);

    if (outFile.is_open()) {
        outFile << "### " << ENGINE_DEFAULTS::ENGINE_NAME
                << " Version: " << ENGINE_DEFAULTS::ENGINE_VERSION
                << " - LuaAPI Reference" << std::endl << std::endl << std::endl;

        std::vector<LuaExportObject>::iterator it = LuaExportAPI::mExports.begin();
        
        while(it != LuaExportAPI::mExports.end()) {
            outFile << "* ";

            if (it->type == LuaExportType::FUNCTION) {
                outFile << "**Function** ";
            }

            outFile << "`";
            outFile << it->returnType << " ";
            outFile << it->name << "(" << it->args << ")";
            outFile << "`";
        
            if (it->comments != "") {
                outFile << " - " << it->comments;
            }

            outFile << std::endl;

            it++;
        }

        outFile.close();
        return true;
    } else {
        LOG << Log::WARNING
            << "[LuaExportAPI::generateFunctionsList] "
            << "Could not open the file: " + fileName
            << std::endl;
    }

    return false;
}

std::string LuaExportAPI::getPredictions(const std::string& name) {
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
        auto it  = LuaExportAPI::mExports.begin();
        auto end = LuaExportAPI::mExports.end();

        // serach for possibles functions
        for(; it != end; it++) {
            if (it->name.find(name) == 0) {
                options.push_back(it->name);
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

