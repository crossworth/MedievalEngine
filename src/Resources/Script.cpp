/*
* @Author: Pedro Henrique
* @Date:   2016-06-16 00:32:53
* @Last Modified by:   Pedro Henrique
* @Last Modified time: 2016-06-16 20:18:56
*/

#include "Script.h"

using namespace ME;

Script::Script(const std::string &fileName) {
	mType       = Resource::Type::SCRIPT;
	mIsValid    = true;
	mScriptCode = Script::load(fileName);
}

std::string Script::getScriptCode() {
	return mScriptCode;
}

std::string Script::load(const std::string &fileName) {
	std::fstream file;
	std::string output   = "";
	std::string fileOpen = ENGINE_DEFAULTS::SCRIPTS_PATH + fileName;

    file.open(fileOpen.c_str(), std::ios::in);

    if (file.is_open()) {
    	std::stringstream strStream;
		strStream << file.rdbuf();
		output = strStream.str();
		file.close();
    }
    
    return output;
}