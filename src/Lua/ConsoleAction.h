
/*
* @Project MedievalEngine
* @Author: Pedro Henrique - system.pedrohenrique@gmail.com
* @Website: http://pedrohenrique.ninja
* @Date:   2016-06-01 13:15:16
*
*
* @File: ConsoleAction.cpp
* @Last Modified by:   Pedro Henrique
* @Last Modified time: 2016-06-01 13:15:23
*/

#ifndef MEDIEVALENGINE_LUA_CONSOLEACTION_H_
#define MEDIEVALENGINE_LUA_CONSOLEACTION_H_

#include "Helper/String.h"

namespace ME {

struct ConsoleAction {
	String command;
	size_t cursorPosition;
};

}

#endif // MEDIEVALENGINE_LUA_CONSOLEACTION_H_
