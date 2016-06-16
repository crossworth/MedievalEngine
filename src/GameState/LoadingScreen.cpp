#include "LoadingScreen.h"

using namespace ME;


LoadingScreen::LoadingScreen() {
    if(LuaAPI::executeScript("pre_loader.lua")) {
    	LuaAPI::script("load()");
    }
}

LoadingScreen::~LoadingScreen() {

}

void LoadingScreen::update(const uint64 &delta) {

}

void LoadingScreen::handleEvents(Event &evt) {

}

void LoadingScreen::draw(Window &window) {

}

void LoadingScreen::pause() {

}

void LoadingScreen::resume() {

}
