#include "Window.h"

using namespace ME;

Window::Window() {
    mWindow = new sf::RenderWindow();
}

Window::~Window() {
    delete mWindow;
}

void Window::create(const WindowInfo& info) {
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

bool Window::isValidWindow(const WindowInfo& info) {
    if (!info.fullScreen) {
        return true;
    }

    sf::VideoMode tmp(info.width, info.height, info.bitsPerPixel);
    return  tmp.isValid();
}

void Window::clear() {
    mWindow->clear();
}

void Window::draw(Drawable* obj) {
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


    switch (sfEvent.type) {
    case sf::Event::Closed:
        evt.type = Event::EventType::Closed;
        break;
    case sf::Event::Resized:
        evt.type        = Event::EventType::Resized;
        evt.size.width  = sfEvent.size.width;
        evt.size.height = sfEvent.size.height;
        break;
    case sf::Event::LostFocus:
        evt.type = Event::EventType::LostFocus;
        break;
    case sf::Event::GainedFocus:
            evt.type = Event::EventType::GainedFocus;
        break;
    case sf::Event::TextEntered:
        evt.type         = Event::EventType::TextEntered;
        evt.text.unicode = sfEvent.text.unicode;
        break;
    case sf::Event::KeyPressed:
        evt.type        = Event::EventType::KeyPressed;
        evt.key.code    = static_cast<Keyboard::KEY>(sfEvent.key.code);
        evt.key.alt     = sfEvent.key.alt;
        evt.key.control = sfEvent.key.control;
        evt.key.shift   = sfEvent.key.shift;
        evt.key.system  = sfEvent.key.system;
        break;
    case sf::Event::KeyReleased:
        evt.type        = Event::EventType::KeyReleased;
        evt.key.code    = static_cast<Keyboard::KEY>(sfEvent.key.code);
        evt.key.alt     = sfEvent.key.alt;
        evt.key.control = sfEvent.key.control;
        evt.key.shift   = sfEvent.key.shift;
        evt.key.system  = sfEvent.key.system;
        break;
    case sf::Event::MouseWheelMoved:
        evt.type             = Event::EventType::MouseWheelMoved;
        evt.mouseWheel.delta = sfEvent.mouseWheel.delta;
        evt.mouseWheel.x     = sfEvent.mouseWheel.x;
        evt.mouseWheel.y     = sfEvent.mouseWheel.y;
        break;
    case sf::Event::MouseWheelScrolled:
        evt.type                   = Event::EventType::MouseWheelScrolled;
        evt.mouseWheelScroll.wheel = static_cast<Mouse::Wheel>(sfEvent.mouseWheelScroll.wheel);
        evt.mouseWheelScroll.delta = sfEvent.mouseWheelScroll.delta;
        evt.mouseWheelScroll.x     = sfEvent.mouseWheelScroll.x;
        evt.mouseWheelScroll.y     = sfEvent.mouseWheelScroll.y;
        break;
    case sf::Event::MouseButtonPressed:
        evt.type               = Event::EventType::MouseButtonPressed;
        evt.mouseButton.button = static_cast<Mouse::Button>(sfEvent.mouseButton.button);
        evt.mouseButton.x      = sfEvent.mouseButton.x;
        evt.mouseButton.y      = sfEvent.mouseButton.y;
        break;
    case sf::Event::MouseButtonReleased:
        evt.type               = Event::EventType::MouseButtonReleased;
        evt.mouseButton.button = static_cast<Mouse::Button>(sfEvent.mouseButton.button);
        evt.mouseButton.x      = sfEvent.mouseButton.x;
        evt.mouseButton.y      = sfEvent.mouseButton.y;
        break;
    case sf::Event::MouseMoved:
        evt.type        = Event::EventType::MouseMoved;
        evt.mouseMove.x = sfEvent.mouseMove.x;
        evt.mouseMove.y = sfEvent.mouseMove.y;
        break;
    case sf::Event::MouseEntered:
        evt.type = Event::EventType::MouseEntered;
        break;
    case sf::Event::MouseLeft:
        evt.type = Event::EventType::MouseLeft;
        break;
    }

    return ret;
}

Vect2i Window::getPosition() {
    sf::Vector2i pos = mWindow->getPosition();
    return Vect2i(pos.x, pos.y);
}

void Window::setPosition(const Vect2i& pos) {
    mWindow->setPosition(sf::Vector2i(pos.x, pos.y));
}

Vect2i Window::getSize() {
    sf::Vector2u size = mWindow->getSize();
    return Vect2i(size.x, size.y);
}

void Window::setSize(const Vect2i& size) {
    mWindow->setSize(sf::Vector2u(size.x, size.y));
}

void Window::setTile(const std::string& title) {
    mWindow->setTitle(title);
}

void Window::setIcon(const std::string& fileName) {
    sf::Image iconImage;
    if (iconImage.loadFromFile(ME::ENGINE_DEFAULTS::ASSETS_PATH + fileName)) {
        mWindow->setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());
    }

}

void Window::setVisible(const bool& visible) {
    mWindow->setVisible(visible);
}

void Window::display() {
    mWindow->display();
}

sf::RenderWindow* Window::getWindowPtr() {
    return mWindow;
}

WindowInfo* Window::getWindowInfo() {
    return &mWindowInfo;
}
