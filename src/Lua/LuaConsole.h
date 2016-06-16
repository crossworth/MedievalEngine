/*
* @Project MedievalEngine
* @Author: Pedro Henrique - system.pedrohenrique@gmail.com
* @Website: http://pedrohenrique.ninja
* @Date:   2016-05-31 21:40:36
*
*
* @File: LuaConsole.cpp
* @Last Modified by:   Pedro Henrique
* @Last Modified time: 2016-06-01 12:50:26
*/

#ifndef MEDIEVALENGINE_LUA_LUACONSOLE_H_
#define MEDIEVALENGINE_LUA_LUACONSOLE_H_

#include <deque>
#include <stack>

#include "Lua/ConsoleAction.h"
#include "Helper/KeyMapper.h"
#include "Helper/Clipboard.h"
#include "Graphics/Window.h"
#include "Resources/ResourceManager.h"

namespace ME {

class MedievalEngine;

class LuaConsole : public LogObserver {
public:
    LuaConsole();
    ~LuaConsole();

    void registerEngine(MedievalEngine *engine);

    void handleEvents(Event &evt);
    bool isVisible();
    void setVisible(bool visible);
    void draw(Window &window);

    void addMessage(const String &message);
    // used by lua binding to add messages to the console output
    void addMessageStd(const std::string &message);

    void setShowUnicodeKeyCodes(bool show);

    void saveConsoleAction(const String &command, const uint32 &cursorPosition);
private:
    void updateInputText();
    void calculateVisibleTextOutput();
    void calculateVisibleTextOutput(const int32 &lineNumber);

    void setTextSelection(const int32 &start, const int32 &end);
    void removeTextSelection();
    bool hasTextSelected();
    String getTextSelected();
      
    // Current command been typed
    String mInputCommand;

    // all the messages that we have info
    // we store on a vector and access as lines
    std::vector<String> mOutputCommands;
    
    // graphics
    Text* mInputText;
    Text* mOutputText;

    Shape* mConsoleShape;
    Shape* mInputLineShape;
    Shape* mSelectedShape;
    Shape* mCursorShape;

    // console configs
    bool mIsConsoleVisible;
    uint32 mMaxNumberLines;
    float mLineHeight;
    float mFontWidth;
    int mFontHeight;
    Vect2i mWindowSize;
    Vect2i mConsoleSize;
    Vect2f mMargin;

    Color mBackgroundColor;

    // auto special char complete (), {}, []
    unsigned int mLastChar;

    // undo
    std::stack<ConsoleAction> mActions;

    //cusor select
    int32 mStartSelect;
    bool mIsTextSelected;
    int32 mStartSelectionPosition;
    int32 mEndSelectionPosition;

    // scroll content
    bool mHasScrolled;
    int mStepScroll;

    // commands history
    std::deque<String> mCommands;
    int mCommandIndex;
    bool mHasMadeAction;

    // debug key codes
    bool mShowKeyCode;

    // cursor position
    int32 mCursorPosition;
    bool mShowCursor;

    // cursor blink
    bool mCursorBlinking;
    Clock mClockCursorBlinking;
    unsigned int mCusorBlinkTime;

    // console current showing text
    uint32 mCurrentOutputLine;
};

}

#endif // MEDIEVALENGINE_LUA_LUACONSOLE_H_
