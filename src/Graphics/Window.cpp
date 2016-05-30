#include "Window.h"
#include "GUI/Widget.h"

using namespace ME;

WindowInfo Window::mWindowInfo;

Window::Window() : mIsWindowOpen(false), mFPS(0), mFrame(0), 
    mHasCustomCursor(false), mCursorVisible(true), mIsWindowVisible(false) {

    mWindow = new sf::RenderWindow();


    // expose some lua functions
    LuaAPI::state.set_function("window_is_open", &Window::isOpen, this);
    LuaExportAPI::exports("window_is_open", "", "bool", LuaExportType::FUNCTION, "if the window is open or not, a hiden window still return true, to check if the window is visible use `window_is_visible`");

    LuaAPI::state.set_function("window_set_title", &Window::setTitle, this);
    LuaExportAPI::exports("window_set_title", "string", "void", LuaExportType::FUNCTION, "set the engine window title");

    LuaAPI::state.set_function("window_set_icon", &Window::setIcon, this);
    LuaExportAPI::exports("window_set_icon", "string", "void", LuaExportType::FUNCTION, "set the engine window icon, must provide a path for an image file on ME::ENGINE_DEFAULTS::ASSETS_PATH folder");

    LuaAPI::state.set_function("window_set_visible", &Window::setVisible, this);
    LuaExportAPI::exports("window_set_visible", "bool", "void", LuaExportType::FUNCTION, "set the window to be visible");

    LuaAPI::state.set_function("window_set_visible", &Window::setVisible, this);
    LuaExportAPI::exports("window_is_visible", "bool", "void", LuaExportType::FUNCTION, "if the window to be visible or not");

    LuaAPI::state.set_function("window_set_cursor", &Window::setCursor, this);
    LuaExportAPI::exports("window_set_cursor", "string", "void", LuaExportType::FUNCTION, "set the window cursor and hide the default window cursor, must provide a path for the a image file on ME::ENGINE_DEFAULTS::ASSETS_PATH folder");

    LuaAPI::state.set_function("window_has_custom_cursor", &Window::hasCustomCursor, this);
    LuaExportAPI::exports("window_has_custom_cursor", "", "bool", LuaExportType::FUNCTION, "if the window has a custom cursor or not");

    LuaAPI::state.set_function("window_get_delta", &Window::getDelta, this);
    LuaExportAPI::exports("window_get_delta", "", "MEUInt64", LuaExportType::FUNCTION, "get the delta time (the time that each frame is using to draw on screen in microseconds)");

    LuaAPI::state.set_function("window_get_fps", &Window::getFPS, this);
    LuaExportAPI::exports("window_get_fps", "", "unsigned int", LuaExportType::FUNCTION, "get the fps counter");

    LuaAPI::state.set_function("window_get_draw_calls", &Window::getDrawCalls, this);
    LuaExportAPI::exports("window_get_draw_calls", "", "unsigned int", LuaExportType::FUNCTION, "get the number of draw made on a single frame, should be called after the last draw call");

    LuaAPI::state.set_function("window_set_cursor_visible", &Window::setCursorVisible, this);
    LuaExportAPI::exports("window_set_cursor_visible", "bool", "void", LuaExportType::FUNCTION, "set the System cursor visible or not, don't have an effect if a custom cursor is set");

    LuaAPI::state.set_function("window_get_position", [this]() -> sol::table {
        Vect2i pos = this->getPosition();

        sol::table result = LuaAPI::state.create_table();

        result["x"] = pos.x;
        result["y"] = pos.y;

        return result;
    });
    LuaExportAPI::exports("window_get_position", "", "table", LuaExportType::FUNCTION, "get the window position, return a table with members: x, y");
    
}

void Window::setCursorVisible(const bool& visible) {
    mCursorVisible = visible;

    if (mWindow != nullptr && mHasCustomCursor == false) {
        if (visible == true) {
            mWindow->setMouseCursorVisible(true);
        } else {
            mWindow->setMouseCursorVisible(false);
        }
    }
}

void Window::setCursor(const std::string& cursor) {
    // Try to load the cursor file, if fails just do a log and nothing more
    // We dont use our ResourceManager here for better performance and control
    // of the existence of our cursor texture and sprite
    if (mCursorTexture.loadFromFile(ME::ENGINE_DEFAULTS::DATA_PATH + cursor)) {
        mHasCustomCursor = true;
        // Disable the default system cursor
        mWindow->setMouseCursorVisible(false);
        mCursor.setTexture(mCursorTexture, true);
        LOG << Log::VERBOSE << "[Window::setCursor] Custom cursor set: "
            << ME::ENGINE_DEFAULTS::DATA_PATH + cursor << std::endl;
    } else {
        LOG << Log::WARNING << "[Window::setCursor] Custom cursor not found: "
            << ME::ENGINE_DEFAULTS::DATA_PATH + cursor << std::endl;
    }
}

bool Window::hasCustomCursor() {
    return mHasCustomCursor;
}

Window::~Window() {
    delete mWindow;
}

void Window::setSizeFullScreen(Drawable* object) {
    Vect2f objectSize;
    // Get the real object size
    objectSize.x = object->getLocalBounds().width;
    objectSize.y = object->getLocalBounds().height;

    // Calculate the ratio based on the minimum size of the Drawable
    // For exemple:
    // If the width of the screen is 700 and height is 500
    // and the Drawable has a resolution of 1000x700
    // we scale the Drawable so that the Drawable height (min size)
    // Can fit on the height of the screen
    // This way we dont distort the Drawable aspect ratio
    int minWin    = std::min(Window::mWindowInfo.width, Window::mWindowInfo.height);
    float minSize = std::min(objectSize.x, objectSize.y);
    float ratio   = minWin / minSize;

    objectSize.x = objectSize.x * ratio;
    objectSize.y = objectSize.y * ratio;

    object->setSize(objectSize);
}

int Window::fontSize(const float& size) {
    int minWin = std::min(Window::mWindowInfo.width, Window::mWindowInfo.height);

    float fontSize = size;

    // Max font size is 1.0f
    // if we pass that point we just reset it to 1.0f
    if (fontSize > 1.0f) {
        fontSize = 1.0f;
    }

    // We than normalize the font size
    // by a  const value that we found during experimentation
    fontSize = fontSize / 10.f;

    // And finally we just convert it to a value based on the
    // screen min size
    return static_cast<int>(minWin * fontSize);
}

void Window::setRelative(Drawable* object) {
    // This function just scale an image to base width and size of the textures
    // definied on the configuration file
    //
    // Exemple: If we are creating resources on a 1920x1080 resolution
    // We can then resize the resources for the resolution utilized during creation
    // and don't worry about the aspect ratio of the image
    Vect2f objectSize = object->getSize();

    int minWin    = std::min(Window::mWindowInfo.width, Window::mWindowInfo.height);
    float minSize = static_cast<float>(std::min(ENGINE_DEFAULTS::BASE_WIDTH_SIZE,
                                                ENGINE_DEFAULTS::BASE_HEIGHT_SIZE));
    float ratio = minWin / minSize;

    objectSize.x = objectSize.x * ratio;
    objectSize.y = objectSize.y * ratio;

    object->setSize(objectSize);
}

void Window::setPosition(Drawable* object, const Window::Position& posX, const Window::Position& posY, Drawable* reference) {
    // TODO(Pedro): Create a innerPadding variables to keep the current padding
    // of the elements inside the window/drawable so this way we get a more
    // CSS like style of padding and avoid using that bullshit of setting the
    // padding to a higher and higher value each time

    // We can't use the getOrigin since it's not right if the object has been resized
    Vect2f origin = object->getOriginRelative();

    Vect2f position(0.f, 0.f);

    float width  = static_cast<float>(Window::mWindowInfo.width);
    float height = static_cast<float>(Window::mWindowInfo.height);

    // base variables for position, so if we are relative to an Drawable
    // we can set the position of the Drawable + the object we want to draw
    float baseX = 0.f;
    float baseY = 0.f;

    // We set the padding variables based on the window width
    // TODO(Pedro): With our CSS like padding, probabily we
    // will have to do some padding + previusPaddig or something
    float paddingLeft   = Window::mWindowInfo.width * object->mPaddingLeft;
    float paddingRight  = Window::mWindowInfo.width * object->mPaddingRight;
    float paddingTop    = Window::mWindowInfo.height * object->mPaddingTop;
    float paddingBottom = Window::mWindowInfo.height * object->mPaddingBottom;

    // If we are relative to an Drawable
    if (reference != nullptr) {
        // We get the current object size and not the localBounds to perform this operation
        Vect2f referenceSize = reference->getSize();

        // Update the variables so we can have relatives values
        width  = referenceSize.x;
        height = referenceSize.y;
        baseX  = reference->getPosition().x;
        baseY  = reference->getPosition().y;

        // And finally update the padding size
        // TODO(Pedro): With our CSS like padding, probabily we
        // will have to do some padding + previusPaddig or something
        paddingLeft   = referenceSize.x * object->mPaddingLeft;
        paddingRight  = referenceSize.x * object->mPaddingRight;
        paddingTop    = referenceSize.y * object->mPaddingTop;
        paddingBottom = referenceSize.y * object->mPaddingBottom;
    }

    // Handle the positions

    if (posX == Window::Position::LEFT) {
        position.x = paddingLeft + baseX + origin.x;
    } else if (posX == Window::Position::RIGHT) {
        position.x = paddingRight + baseX + width - object->getSize().x + origin.x;
    } else if (posX == Window::Position::CENTER) {
        position.x = baseX + ((width / 2) - (object->getSize().x / 2) + origin.x);
    }

    if (posY == Window::Position::TOP) {
        position.y = paddingTop + baseY + origin.y;
    } else if (posY == Window::Position::BOTTOM) {
        position.y = paddingBottom + baseY + height - object->getSize().y + origin.y;;
    } else if (posY == Window::Position::CENTER) {
        position.y = baseY + ((height / 2) - (object->getSize().y / 2) + origin.y);
    }

    object->setPosition(position);
}

void Window::setPosition(WidgetPtr object, const Window::Position& posX, const Window::Position& posY, Drawable* reference) {
    // We just call our setPosition function dereferencing the smartpointer
    Window::setPosition(object.get(), posX, posY, reference);
}

void Window::open() {
    if (!mIsWindowOpen) {
        sf::ContextSettings settings;
        // Default antialiasing Level
        // We don't provide a way to change this
        // since it's relave inexpensive
        settings.antialiasingLevel = 8;

        if (Window::mWindowInfo.fullScreen) {
            mWindow = new sf::RenderWindow(
                        sf::VideoMode(Window::mWindowInfo.width, Window::mWindowInfo.height, Window::mWindowInfo.bitsPerPixel),
                        Window::mWindowInfo.windowName.getWideString(), sf::Style::Fullscreen, settings);
        } else {
            mWindow = new sf::RenderWindow(
                        sf::VideoMode(Window::mWindowInfo.width, Window::mWindowInfo.height, Window::mWindowInfo.bitsPerPixel),
                        Window::mWindowInfo.windowName.getWideString(), sf::Style::Close, settings);
        }

        // We get an default view for drawing the cursor at end
        mFixedView = mWindow->getView();

        mWindow->setFramerateLimit(Window::mWindowInfo.frameLimit);
        mWindow->setVerticalSyncEnabled(Window::mWindowInfo.vsync);

        // Finally we open the window and reset the default clock time
        mIsWindowOpen = true;
        mClock.restart();

        LOG << Log::VERBOSE << "[Window::open] Window opened" << std::endl;
        mIsWindowVisible = true;
    }
}

void Window::create(const WindowInfo& info) {
    // If we are trying to create a Fullscreen window
    // We must verify if it's a valid window first
    // if not we just set the fullScreen to false
    // since a non-fullscreen window are always valid
    if (info.fullScreen == true && isValidWindow(info)) {
        Window::mWindowInfo.fullScreen = true;
    } else {
        Window::mWindowInfo.fullScreen = false;
    }

    Window::mWindowInfo.bitsPerPixel = info.bitsPerPixel;
    Window::mWindowInfo.height       = info.height;
    Window::mWindowInfo.width        = info.width;
    Window::mWindowInfo.windowName   = info.windowName;
    Window::mWindowInfo.frameLimit   = info.frameLimit; 
    Window::mWindowInfo.vsync        = info.vsync; 

    LOG << Log::VERBOSE << "[Window::create] Window created" << std::endl;
}

MEUInt64 Window::getDelta() {
    return mDelta;
}

unsigned int Window::getFPS() {
    return mFPS;
}

bool Window::isValidWindow(const WindowInfo& info) {
    // non-fullscreen windows are always valid
    if (!info.fullScreen) {
        return true;
    }

    sf::VideoMode tmp(info.width, info.height, info.bitsPerPixel);
    return tmp.isValid();
}

void Window::clear() {
    mDrawCalls = 0;
    mWindow->clear();
}

void Window::draw(Drawable* obj) {
    assert(obj != nullptr);
    obj->draw(*this);

    mDrawCalls++;
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

    // If we have a custom cursor we update its position
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

void Window::setTitle(const std::string& title) {
    mWindow->setTitle(title);
}

unsigned int Window::getDrawCalls() {
    return mDrawCalls;
}

void Window::setIcon(const std::string& fileName) {
    // TODO(Pedro): Verify if this work as expected since
    // it can cause a pointer dereferencing early
    // since iconImage is local variable
    sf::Image iconImage;
    if (iconImage.loadFromFile(ME::ENGINE_DEFAULTS::ASSETS_PATH + fileName)) {
        mWindow->setIcon(iconImage.getSize().x,
                         iconImage.getSize().y,
                         iconImage.getPixelsPtr());
    }

}

void Window::setVisible(const bool& visible) {
    mIsWindowVisible = visible;
    mWindow->setVisible(visible);

}

bool Window::isVisible() {
    return mIsWindowVisible;
}

void Window::display() {
    // We have to draw the cursor on the display method
    // the draw method can and is called multiple times
    // the display method should be called only one time
    {
        ProfileBlockStr("set cursor and draw");  
        if (hasCustomCursor() && mCursorVisible) {
            mWindow->setView(mFixedView);
            mWindow->draw(mCursor);
        }
    }

    {
        ProfileBlockStr("SFML internal display");  
        mWindow->display();
    }

    // calc delta
    mDelta = mClock.getMicroSeconds() - mLastDelta;
    
    // calc fps
    if(mClock.getSeconds() >= 1.f) {
        mFPS = mFrame;
        mFrame = 0;
        mClock.restart();
    }

    ++mFrame;

    // we have to define the new delta after the fps calc, since it can restart the clock
    mLastDelta = mClock.getMicroSeconds();
}

sf::RenderWindow* Window::getWindowPtr() {
    return mWindow;
}

WindowInfo* Window::getWindowInfo() {
    return &Window::mWindowInfo;
}
