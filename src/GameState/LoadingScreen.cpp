#include "LoadingScreen.h"

using namespace ME;


LoadingScreen::LoadingScreen() {
	LuaAPI::executeScript("loadingscreen_init.lua");
}

LoadingScreen::~LoadingScreen() {

}

void LoadingScreen::update(const uint64 &delta) {
	LuaAPI::executeScript("loadingscreen_update.lua");
}

void LoadingScreen::handleEvents(Event &evt) {
	LuaAPI::executeScript("loadingscreen_events.lua");
}

void LoadingScreen::draw(Window &window) {
	LuaAPI::executeScript("loadingscreen_draw.lua");
}

void LoadingScreen::pause() {
	LuaAPI::executeScript("loadingscreen_pause.lua");
}

void LoadingScreen::resume() {
	LuaAPI::executeScript("loadingscreen_resume.lua");
}
