#include "LoadingScreen.h"

using namespace ME;


LoadingScreen::LoadingScreen() {

}

LoadingScreen::~LoadingScreen() {

}

void LoadingScreen::update(const uint64 &delta) {
	if (LuaAPI::executeScript("loading_thread.lua")) {
        LuaAPI::script("load()");
    }
}

void LoadingScreen::handleEvents(Event &evt) {

}

void LoadingScreen::draw(Window &window) {

}

void LoadingScreen::pause() {

}

void LoadingScreen::resume() {

}
