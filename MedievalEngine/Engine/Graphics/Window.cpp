#include "Window.h"
#include "GUI/Widget.h"

using namespace ME;

WindowInfo Window::mWindowInfo;

Window::Window() : mIsWindowOpen(false), mHasCustomCursor(false) {
    mWindow = new sf::RenderWindow();
}

void Window::setCursor(const std::string& cursor) {
    if (mCursorTexture.loadFromFile(ME::ENGINE_DEFAULTS::DATA_PATH + cursor)) {
        mHasCustomCursor = true;
        mWindow->setMouseCursorVisible(false);
        mCursor.setTexture(mCursorTexture, true);
        LOG << Log::VERBOSE << "[Window::setCursor] Custom cursor set: "
            << ME::ENGINE_DEFAULTS::DATA_PATH + cursor << std::endl;
    } else {
        LOG << Log::VERBOSE << "[Window::setCursor] Custom not found: "
            << ME::ENGINE_DEFAULTS::DATA_PATH + cursor << std::endl;
    }
}

bool Window::hasCustomCursor() {
    return mHasCustomCursor;
}

Window::~Window() {
    delete mWindow;
}

void Window::fullScreen(Drawable* object) {
    Vect2f objectSize;
    objectSize.x = object->getLocalBounds().width;
    objectSize.y = object->getLocalBounds().height;

    int minWin    = std::min(Window::mWindowInfo.width, Window::mWindowInfo.height);
    float minSize = std::min(objectSize.x, objectSize.y);
    float ratio   = minWin / minSize;

    objectSize.x = objectSize.x * ratio;
    objectSize.y = objectSize.y * ratio;

    object->setSize(objectSize);
}

int Window::fontSize(const float& size) {
    int minWin = std::min(Window::mWindowInfo.width, Window::mWindowInfo.height);

    float sizeTmp = size;
    if (sizeTmp > 1.f) {
        sizeTmp = 1.f;
    }

    float fontSize = sizeTmp / 10.f;

    return static_cast<int>(minWin * fontSize);
}

void Window::setRelative(Drawable* object) {
    Vect2f objectSize = object->getSize();

    int minWin    = std::min(Window::mWindowInfo.width, Window::mWindowInfo.height);
    float minSize = static_cast<float>(std::min(ENGINE_DEFAULTS::BASE_WIDTH_SIZE,
                                                ENGINE_DEFAULTS::BASE_HEIGHT_SIZE));
    float ratio   = minWin / minSize;

    objectSize.x = objectSize.x * ratio;
    objectSize.y = objectSize.y * ratio;

    object->setSize(objectSize);
}

void Window::setPosition(Drawable* object, const Window::Position& posX, const Window::Position& posY, Drawable* reference) {
    Vect2f origin = object->getOriginRelative();

    Vect2f position(0.f, 0.f);

    float width  = static_cast<float>(Window::mWindowInfo.width);
    float height = static_cast<float>(Window::mWindowInfo.height);

    float baseX = 0.f;
    float baseY = 0.f;


    float paddingLeft   = Window::mWindowInfo.width * object->mPaddingLeft;
    float paddingRight  = Window::mWindowInfo.width * object->mPaddingRight;
    float paddingTop    = Window::mWindowInfo.height * object->mPaddingTop;
    float paddingBottom = Window::mWindowInfo.height * object->mPaddingBottom;

    if (reference != nullptr) {
        Vect2f referenceSize = reference->getSize();
        width  = referenceSize.x;
        height = referenceSize.y;
        baseX  = reference->getPosition().x;
        baseY  = reference->getPosition().y;

        paddingLeft   = referenceSize.x * object->mPaddingLeft;
        paddingRight  = referenceSize.x * object->mPaddingRight;
        paddingTop    = referenceSize.y * object->mPaddingTop;
        paddingBottom = referenceSize.y * object->mPaddingBottom;
    }

    if (posX == Window::Position::LEFT) {
        position.x = paddingLeft + baseX + 0.0f + origin.x;
    } else if (posX == Window::Position::RIGHT) {
        position.x = paddingRight + baseX + width - object->getSize().x + origin.x;
    } else if (posX == Window::Position::CENTER) {
        position.x = baseX + ((width / 2) - (object->getSize().x / 2) + origin.x);
    }

    if (posY == Window::Position::TOP) {
        position.y = paddingTop + baseY + 0.0f + origin.y;
    } else if (posY == Window::Position::BOTTOM) {
        position.y = paddingBottom + baseY + height - object->getSize().y + origin.y;;
    } else if (posY == Window::Position::CENTER) {
        position.y = baseY + ((height / 2) - (object->getSize().y / 2) + origin.y);
    }

    object->setPosition(position);
}

void Window::setPosition(WidgetPtr object, const Window::Position& posX, const Window::Position& posY, Drawable* reference) {
    Window::setPosition(object.get(), posX, posY, reference);
}

void Window::open() {
    if (!mIsWindowOpen) {
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        if (Window::mWindowInfo.fullScreen) {
            mWindow = new sf::RenderWindow(
                        sf::VideoMode(Window::mWindowInfo.width, Window::mWindowInfo.height, Window::mWindowInfo.bitsPerPixel),
                        Window::mWindowInfo.windowName, sf::Style::Fullscreen, settings);
        } else {
            mWindow = new sf::RenderWindow(
                        sf::VideoMode(Window::mWindowInfo.width, Window::mWindowInfo.height, Window::mWindowInfo.bitsPerPixel),
                        Window::mWindowInfo.windowName, sf::Style::Close, settings);
        }

        mFixedView = mWindow->getView();

        mWindow->setFramerateLimit(Window::mWindowInfo.frameLimit);
        mWindow->setVerticalSyncEnabled(Window::mWindowInfo.vsync);

        mIsWindowOpen = true;
        mClock.restart();

        LOG << Log::VERBOSE << "[Window::open] Window opened" << std::endl;
    }
}

void Window::create(const WindowInfo& info) {

    if (info.fullScreen == true && isValidWindow(info)) {
        Window::mWindowInfo.fullScreen   = true;
    } else {
        Window::mWindowInfo.fullScreen   = false;
    }


    Window::mWindowInfo.bitsPerPixel = info.bitsPerPixel;
    Window::mWindowInfo.height       = info.height;
    Window::mWindowInfo.width        = info.width;
    Window::mWindowInfo.windowName   = info.windowName;

    LOG << Log::VERBOSE << "[Window::create] Window created" << std::endl;
}

unsigned int Window::getDelta() {
    return mClock.getTime();
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
    mClock.restart();
}

void Window::draw(Drawable* obj) {
    assert(obj != nullptr);
    if (obj->requireWindowObject()) {
        obj->draw(*this);
    } else {
        obj->draw(mWindow);
    }

}

void Window::draw(Drawable *obj, sf::RenderStates* states) {
    assert(obj != nullptr);
    if (obj->requireWindowObject()) {
        obj->draw(*this);
    } else {
        obj->draw(mWindow, states);
    }
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

    if (hasCustomCursor()) {
        mCursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*mWindow)));
    }

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
    // TODO(Pedro): Verificar compatibilidade com nova versão do SFML
    // case sf::Event::MouseWheelMoved:
    //     evt.type             = Event::EventType::MouseWheelMoved;
    //     evt.mouseWheel.delta = sfEvent.mouseWheel.delta;
    //     evt.mouseWheel.x     = sfEvent.mouseWheel.x;
    //     evt.mouseWheel.y     = sfEvent.mouseWheel.y;
    //     break;
    // case sf::Event::MouseWheelScrolled:
    //     evt.type                   = Event::EventType::MouseWheelScrolled;
    //     evt.mouseWheelScroll.wheel = static_cast<Mouse::Wheel>(sfEvent.mouseWheelScroll.wheel);
    //     evt.mouseWheelScroll.delta = sfEvent.mouseWheelScroll.delta;
    //     evt.mouseWheelScroll.x     = sfEvent.mouseWheelScroll.x;
    //     evt.mouseWheelScroll.y     = sfEvent.mouseWheelScroll.y;
    //     break;
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
    Vect2i size;

    if (mIsWindowOpen) {
        size.x = mWindow->getSize().x;
        size.y = mWindow->getSize().y;
    } else {
        size.x = Window::mWindowInfo.width;
        size.y = Window::mWindowInfo.height;
    }
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
        mWindow->setIcon(iconImage.getSize().x,
                         iconImage.getSize().y,
                         iconImage.getPixelsPtr());
    }

}

void Window::setVisible(const bool& visible) {
    mWindow->setVisible(visible);
}

void Window::display() {
    if (hasCustomCursor()) {
        mWindow->setView(mFixedView);
        mWindow->draw(mCursor);
    }

    mWindow->display();
}

sf::RenderWindow* Window::getWindowPtr() {
    return mWindow;
}

WindowInfo* Window::getWindowInfo() {
    return &Window::mWindowInfo;
}
