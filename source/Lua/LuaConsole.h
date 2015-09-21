#ifndef LUACONSOLE_H
#define LUACONSOLE_H
#include <deque>
#include "Helper/KeyMapper.h"
#include "Lua/LuaAPI.h"
#include "Graphics/Window.h"
#include "Resources/ResourceManager.h"


namespace ME {

class MedievalEngine;

class LuaConsole : public LogObserver {
public:
    LuaConsole();

    void registerEngine(MedievalEngine* engine);

    void handleEvents(Event& evt);
    bool isVisible();
    void setVisible(bool visible);
    void draw(Window& window);

    void addMessage(const sf::String& buffer);
    std::string getToken(const std::string& cmd);

private:
    bool mIsVisible;
    
    ResourceManager* mResources;
        
    // buffer for the text been typed
    sf::String mBuffer;
    std::string cmdBuffer;
    // buffer for the output
    sf::String mBufferOutput;
    sf::View panelView;
    
    Text* mText;
    Text* mOutput;
    Shape* mBG;
    Shape* mLineEdit;

    float mLineHeight;
    int mNumberLines;
    
    Vect2i mWindowSize;
    Vect2i mConsoleSize;
    Vect2f mMargin;
    
    Color mBGColor;

    // scroll content
    bool mHasScrolled;
    int mStepScroll;

    // commands history
    std::deque<std::string> mCommands;
    int mCommandsIndex;
    bool mHasMakeAction;

    // cursor position
    size_t mCursorPosition;
    size_t mCursorPadding;
    bool mCursorMoving;

    // cursor blink
    Clock mClockBlinkCursor;
    sf::String mCursor;
    sf::String mDefaultText;
    unsigned int mCusorBlinkTime;
};

}

#endif // LUACONSOLE_H
