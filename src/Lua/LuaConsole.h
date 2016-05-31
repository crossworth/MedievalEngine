#ifndef LUACONSOLE_H
#define LUACONSOLE_H
#include <deque>
#include "Helper/KeyMapper.h"
#include "Graphics/Window.h"
#include "Resources/ResourceManager.h"


namespace ME {

class MedievalEngine;

class LuaConsole : public LogObserver {
public:
    LuaConsole();
    ~LuaConsole();

    void registerEngine(MedievalEngine* engine);

    void handleEvents(Event& evt);
    bool isVisible();
    void setVisible(bool visible);
    void draw(Window& window);

    void addMessage(const String& buffer);
    void addMessageStd(const std::string& buffer);

    void setShowUnicodeKeyCodes(bool debug);

private:
    void setTextSelection(const size_t& start, const size_t& end);
    void setNoTextSelection();
    bool hasTextSelected();
    String getTextSelected();


    bool mIsVisible;
    
    ResourceManager* mResources;
        
    // buffer for the text been typed
    String mBuffer;
    std::string cmdBuffer;
    // buffer for the output
    String mBufferOutput;
    sf::View panelView;
    
    Text* mText;
    Text* mOutput;
    Shape* mBG;
    Shape* mLineEdit;
    Shape* mShapeSelected;

    float mLineHeight;
    
    Vect2i mWindowSize;
    Vect2i mConsoleSize;
    Vect2f mMargin;
    
    Color mBGColor;

    unsigned int mLastChar;

    //cusor select
    size_t mStartSelect;
    bool mIsTextSelected;
    size_t mStartSelectionPosition;
    size_t mEndSelectionPosition;

    // scroll content
    bool mHasScrolled;
    int mStepScroll;

    // commands history
    std::deque<std::string> mCommands;
    int mCommandsIndex;
    bool mHasMakeAction;

    // debug key codes
    bool mDebugKeyCodes;

    // cursor position
    size_t mCursorPosition;
    bool mCursorMoving;

    // cursor blink
    bool mCursorBlinking;
    Clock mClockBlinkCursor;
    Shape* mShapeCursor;
    size_t mFontLetterSize;
    unsigned int mCusorBlinkTime;
};

}

#endif // LUACONSOLE_H
