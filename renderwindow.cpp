#include "renderwindow.h"

using namespace ME;

renderWindow::renderWindow() : mWindowInfomation(ENGINE_DEFAULTS::WIDTH_WINDOW, ENGINE_DEFAULTS::HEIGHT_WINDOW, ENGINE_DEFAULTS::BITS_PER_PIXEL_WINDOW, ENGINE_DEFAULTS::FULLSCREEN_WINDOW, ENGINE_DEFAULTS::ENGINE_NAME) {
   dbg = Debugger::getInstance();

}

Coord renderWindow::getCameraPosition(const std::string &name) {
    Coord tmp;
    tmp.x = getCamera(name)->getCenter().x - getCamera(name)->getSize().x/2;
    tmp.y = getCamera(name)->getCenter().y - getCamera(name)->getSize().y/2;
    return tmp;
}

void renderWindow::createWindow(const windowInformation winInfos, int frameLimit, bool vsync) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    if (winInfos.fullScreen == true && isValidWindow(winInfos)) {
        Window = new sf::RenderWindow(sf::VideoMode(winInfos.width, winInfos.height, winInfos.bitsPerPixel), winInfos.windowName, sf::Style::Fullscreen, settings);
    } else {
        Window = new sf::RenderWindow(sf::VideoMode(winInfos.width, winInfos.height, winInfos.bitsPerPixel), winInfos.windowName, sf::Style::Close, settings);
    }

    Window->setFramerateLimit(frameLimit);
    Window->setVerticalSyncEnabled(vsync);

    dbg->log(VERBOSE, 1, "[renderWindow::createWindow] Window created");

}

void renderWindow::setIcon(int width, int height, Image icon) {
    Window->setIcon(width, height, icon.getPixelsPtr());
}

bool renderWindow::pollEvent(Event &evt) {
    return Window->pollEvent(evt);
}

windowInformation renderWindow::getWindowInformation() {
    return mWindowInfomation;
}

bool renderWindow::isValidWindow(const windowInformation winInfos) {
return true;
    // Funciona somente em modo FullScreen
    if (!winInfos.fullScreen)
        return true;

    sf::VideoMode tmp(winInfos.width, winInfos.height, winInfos.bitsPerPixel);
    return  tmp.isValid();
}

sf::RenderWindow * renderWindow::getRenderWindow() {
    return Window;
}

bool renderWindow::isOpen() {
    return Window->isOpen();
}

void renderWindow::clear(const sf::Color &c) {
    Window->clear(c);
}

void renderWindow::display() {
    Window->display();
}

void renderWindow::draw(const sf::Drawable &draw) {
    Window->draw(draw);
}

void renderWindow::close() {
    Window->close();
}

Camera* renderWindow::createCamera(const std::string &name, const FloatRect &rect) {
    mCameras.insert(std::make_pair(name, new Camera(rect)));
    return mCameras[name];
}

Camera* renderWindow::createCamera(const std::string &name, const Camera &cam) {
    mCameras.insert( std::make_pair(name, new Camera(cam)));
    return mCameras[name];
}

Camera* renderWindow::getCamera(const std::string &name) {
    if (name.compare("default")) {
        return  getDefaultCamera();
    } else if (mCameras.find(name) != mCameras.end()) {
        return mCameras[name];
    } else {
        dbg->log(WARNING, 1, ("[renderWindow::getCamera] Camera ("+ name + ") not found").c_str());
        return nullptr;
    }
}

void renderWindow::setCamera(const std::string &name) {
    if (mCameras.find(name) != mCameras.end()) {
        Window->setView(*mCameras[name]);
    } else {
        dbg->log(WARNING, 1,("[renderWindow::setCamera] Camera ("+ name + ") not found").c_str());
    }
}

void renderWindow::setCamera(const Camera &cam) {
    Window->setView(cam);
}

Camera* renderWindow::getDefaultCamera() {
    return (Camera*)&Window->getDefaultView();
}

renderWindow* renderWindow::getInstance() {
    static renderWindow* renderInstance = new renderWindow();
    return renderInstance;
}

renderWindow::~renderWindow() {
    std::map<std::string,Camera*>::iterator it = mCameras.begin();
    for(; it != mCameras.end();it++) {
        delete it->second;
    }
    mCameras.clear();
}
