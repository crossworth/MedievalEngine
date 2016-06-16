#ifndef MEDIEVALENGINE_RESOURCES_SCRIPT_H_
#define MEDIEVALENGINE_RESOURCES_SCRIPT_H_
#include <iostream>
#include <sstream>
#include <fstream>

#include "Config.h"

#include "Resources/Resource.h"

namespace ME {

class Script : public Resource {
public:
    Script(const std::string &fileName);
    std::string getScriptCode();

    static std::string load(const std::string &fileName);
private:
    std::string mScriptCode;
};

}

#endif // MEDIEVALENGINE_RESOURCES_SCRIPT_H_
