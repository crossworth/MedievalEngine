#include "Window.h"

using namespace ME;

Window::Window() {
    mWindow = new sf::RenderWindow();
}

Window::~Window() {

}

void Window::create(const WindowInfo &info) {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    if (info.fullScreen == true && isValidWindow(info)) {
        mWindow = new sf::RenderWindow(sf::VideoMode(info.width, info.height, info.bitsPerPixel), info.windowName, sf::Style::Fullscreen, settings);
    } else {
        mWindow = new sf::RenderWindow(sf::VideoMode(info.width, info.height, info.bitsPerPixel), info.windowName, sf::Style::Close, settings);
    }

    mWindow->setFramerateLimit(info.frameLimit);
    mWindow->setVerticalSyncEnabled(info.vsync);

    // Deixa tela preta enquanto carrega o resto dos recursos e inicia os sistemas
    mWindow->clear();

    mWindowInfo.bitsPerPixel = info.bitsPerPixel;
    mWindowInfo.fullScreen   = info.fullScreen;
    mWindowInfo.height       = info.height;
    mWindowInfo.width        = info.width;
    mWindowInfo.windowName   = info.windowName;

    LOG << Log::VERBOSE << "[Window::create] Window created" << std::endl;
}

bool Window::isValidWindow(const WindowInfo &info) {
    if (!info.fullScreen) {
        return true;
    }

    sf::VideoMode tmp(info.width, info.height, info.bitsPerPixel);
    return  tmp.isValid();
}

void Window::clear() {
    mWindow->clear();
}

void Window::draw(Drawable *obj) {
    assert(obj != nullptr);
    obj->draw(mWindow);
}

void Window::close() {
    mWindow->close();
}

bool Window::isOpen() {
    return mWindow->isOpen();
}

bool Window::pollEvent(Event& evt) {
    sf::Event sfEvent;
    bool ret = mWindow->pollEvent(sfEvent);

    evt.type = static_cast<Event::EventType>(sfEvent.type);
    return ret;
}

Vect2i Window::getPosition() {
    sf::Vector2i pos = mWindow->getPosition();
    return Vect2i(pos.x, pos.y);
}

void Window::setPosition(const Vect2i &pos) {
    mWindow->setPosition(sf::Vector2i(pos.x, pos.y));
}

Vect2i Window::getSize() {
    sf::Vector2u size = mWindow->getSize();
    return Vect2i(size.x, size.y);
}

void Window::setSize(const Vect2i &size) {
    mWindow->setSize(sf::Vector2u(size.x, size.y));
}

void Window::setTile(const std::string &title) {
    mWindow->setTitle(title);
}

void Window::setIcon(unsigned int width, unsigned int height, const sf::Uint8 *pixels) {
    mWindow->setIcon(width, height, pixels);
}

void Window::setVisible(const bool &visible) {
    mWindow->setVisible(visible);
}

void Window::display() {
    mWindow->display();
}
