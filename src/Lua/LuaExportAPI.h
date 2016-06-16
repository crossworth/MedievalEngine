#ifndef LUAEXPORT_API
#define LUAEXPORT_API
#include <string>
#include <vector>
#include <algorithm>
#include "LogInc.h"

namespace ME {

enum class LuaExportType {
	UNKNOWN = 0,
	FUNCTION,
	VARIABLE,
	GLOBAL_VARIABLE
};

struct LuaExportObject {
	std::string name;
	std::string args;
	std::string returnType;
	std::string comments;
	LuaExportType type;
};

class LuaExportAPI {
public:
	static void exports(const std::string &name,
						const std::string &args,
	 					const std::string &returnType,
	 					const LuaExportType &type,
	 					const std::string &comments = "");
   
    static std::string getPredictions(const std::string &name);

    static const std::vector<std::string> getFunctions();

    static bool generateFunctionsList(const std::string &fileName);
private:
    static std::vector<LuaExportObject> mExports;
};

}

#endif // LUAEXPORT_API
