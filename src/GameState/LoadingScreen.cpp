#include "LoadingScreen.h"

using namespace ME;


LoadingScreen::LoadingScreen() {
	LuaAPI::executeScriptSync("loadingscreen_init.lua");
}

LoadingScreen::~LoadingScreen() {

}

void LoadingScreen::update(const uint64 &delta) {
	LuaAPI::executeScriptSync("loadingscreen_update.lua");
}

void LoadingScreen::handleEvents(Event &evt) {
	LuaAPI::executeScriptSync("loadingscreen_events.lua");
}

void LoadingScreen::draw(Window &window) {
	LuaAPI::executeScriptSync("loadingscreen_draw.lua");
}

void LoadingScreen::pause() {
	LuaAPI::executeScriptSync("loadingscreen_pause.lua");
}

void LoadingScreen::resume() {
	LuaAPI::executeScriptSync("loadingscreen_resume.lua");
}
