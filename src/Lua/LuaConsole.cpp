/*
* @Project MedievalEngine
* @Author: Pedro Henrique - system.pedrohenrique@gmail.com
* @Website: http://pedrohenrique.ninja
* @Date:   2016-05-31 21:40:36
*
*
* @File: LuaConsole.cpp
* @Last Modified by:   Pedro Henrique
* @Last Modified time: 2016-06-06 18:49:55
*/

#include "LuaConsole.h"
#include "Engine/MedievalEngine.h"


using namespace ME;

LuaConsole::LuaConsole() {
    mIsConsoleVisible       = false;
    mInputCommand           = "";
    mLastChar               = 0;
    mFontWidth              = 0;
    mInputText              = nullptr;
    mOutputText             = nullptr;
    mConsoleShape           = nullptr;
    mInputLineShape         = nullptr;
    mSelectedShape          = nullptr;
    mCursorShape            = nullptr;
    mBackgroundColor        = Color(0, 0, 0, 120);
    mShowCursor             = false;
    mHasScrolled            = false;
    mCursorBlinking         = false;
    mShowKeyCode            = false;
    mHasMadeAction          = false;
    mStepScroll             = 30;
    mCursorPosition         = 0;
    mCommandIndex           = 0;
    mCusorBlinkTime         = 500;
    mStartSelect            = 0;
    mIsTextSelected         = false;
    mStartSelectionPosition = 0;
    mEndSelectionPosition   = 0;
    mMaxNumberLines         = 0;
    mFontHeight             = 0;
    mCurrentOutputLine      = 0;


    /**
    *   ======== LUA API ========
    *   ======== EXPORTS ========
    **/
    LuaAPI::state.set_function("console_is_visible", &LuaConsole::isVisible, this);
    LuaExportAPI::exports("console_is_visible", "", "bool", LuaExportType::FUNCTION, "if the console is open or not");

    LuaAPI::state.set_function("console_set_visible", &LuaConsole::setVisible, this);
    LuaExportAPI::exports("console_set_visible", "bool", "void", LuaExportType::FUNCTION, "show or hide the console");

    LuaAPI::state.set_function("console_toggle", [this] () {
        if (this->isVisible()) {
            this->setVisible(false);
        } else {
            this->setVisible(true);
        }
    });
    LuaExportAPI::exports("console_toggle", "", "void", LuaExportType::FUNCTION, "show or hide the console");

    LuaAPI::state.set_function("console_close", [this] () {
        this->setVisible(false);
    });
    LuaExportAPI::exports("console_close", "", "void", LuaExportType::FUNCTION, "close the console");

    LuaAPI::state.set_function("console_open", [this] () {
        this->setVisible(true);
    });
    LuaExportAPI::exports("console_open", "", "void", LuaExportType::FUNCTION, "open the console");

    LuaAPI::state.set_function("console_add_message", &LuaConsole::addMessageStd, this);
    LuaExportAPI::exports("console_add_message", "", "void", LuaExportType::FUNCTION, "add an message to the console");

    LuaAPI::state.set_function("console_show_unicode_key_codes", &LuaConsole::setShowUnicodeKeyCodes, this);
    LuaExportAPI::exports("console_show_unicode_key_codes", "", "void", LuaExportType::FUNCTION, "show the unicode codes of pressed keys on console");

    LuaAPI::state.set_function("generate_function_list_file", [this] () {
        LuaExportAPI::generateFunctionsList(ENGINE_DEFAULTS::DATA_PATH + "Lua Reference.md");
    });
    LuaExportAPI::exports("generate_function_list_file", "", "void", LuaExportType::FUNCTION, "generate the Lua Reference.md file on the ENGINE_DEFAULTS::DATA_PATH folder");

    /**
    *   ======== LUA API ========
    *   ======== EXPORTS ========
    **/

    mClockCursorBlinking.restart();
}

void LuaConsole::setShowUnicodeKeyCodes(bool show) {
    mShowKeyCode = show;
}

String LuaConsole::getTextSelected() {
    size_t sizeString = mEndSelectionPosition - mStartSelectionPosition;
    return mInputCommand.substr(mStartSelectionPosition, sizeString);
}

void LuaConsole::saveConsoleAction(const String& command, const size_t& cursorPosition) {
    ConsoleAction tmp;
    tmp.command        = command;
    tmp.cursorPosition = cursorPosition;
    mActions.push(tmp);
}


void LuaConsole::updateInputText() {
    // update the current edit text display position on screen when there is a lot of text
    if ((mCursorPosition * mFontWidth) >= mInputLineShape->getSize().x) {
        float lineDiff      = (mCursorPosition * mFontWidth)  - mInputLineShape->getSize().x;
        Vect2f inputLinePos = mInputLineShape->getPosition();
        inputLinePos.x      = inputLinePos.x - lineDiff;
        mInputText->setPosition(inputLinePos);
    } else {
        mInputText->setPosition(mInputLineShape->getPosition());
    }

    // if we have updated the input text position we have to update the selection text position as well
    if (hasTextSelected()) {
        removeTextSelection();
        setTextSelection(mStartSelectionPosition, mEndSelectionPosition);
    }
}

void LuaConsole::handleEvents(Event& evt) {
    if (evt.type == Event::KeyPressed) {

        if (KeyMapper::action("toggle_console", evt)) {
            if (isVisible()) {
                setVisible(false);
            } else {
                if (!mHasScrolled) {
                    calculateVisibleTextOutput();
                }

                setVisible(true);
            }
        }
    }

    // If the console is visible we handle the rest of the commands on it.
    if(isVisible()) {


        if (evt.type == Event::KeyPressed) {

            // Control + A
            if (evt.key.code == Keyboard::KEY::A && 
                ((evt.key.control && !OS::isMacOS()) || (evt.key.system && OS::isMacOS()))) {
                
                setTextSelection(0, mInputCommand.getSize());
                mCursorPosition = mInputCommand.getSize();
            }

            // Control + V
            if (evt.key.code == Keyboard::KEY::V && 
                ((evt.key.control && !OS::isMacOS()) || (evt.key.system && OS::isMacOS()))) {
                saveConsoleAction(mInputCommand, mCursorPosition);
                String text = Clipboard::getData();

                // clear the string
                text.removeNewLine();
                text.removeCarriageReturn();
                text.removeTab();

                // if has text selected
                if (hasTextSelected()) {
                    // remove all selected
                    int diffCursorPosition = mEndSelectionPosition - mStartSelectionPosition;
                    mShowCursor            = true;
                    mHasMadeAction         = true;

                    mInputCommand.erase(static_cast<int>(mStartSelectionPosition), static_cast<int>(diffCursorPosition));
                    
                    // set the cursor position to the beginer of the selection
                    mCursorPosition = mStartSelectionPosition;
                    removeTextSelection();
                } else {
                    removeTextSelection();
                }

                mInputCommand.insert(mCursorPosition, text);
                mCursorPosition = mCursorPosition + text.getSize();
            }


            // Control + C
            if (evt.key.code == Keyboard::KEY::C && 
                ((evt.key.control && !OS::isMacOS()) || (evt.key.system && OS::isMacOS()))) {
                String text = getTextSelected();
                Clipboard::setData(text);
            }


            // Control + Z
            if (evt.key.code == Keyboard::KEY::Z && 
                ((evt.key.control && !OS::isMacOS()) || (evt.key.system && OS::isMacOS()))) {
                if (mActions.size() > 0) {
                    ConsoleAction tmp = mActions.top();
                    mInputCommand     = tmp.command;
                    mCursorPosition   = tmp.cursorPosition;
                    mActions.pop();
                }
            }

            if (evt.key.code == Keyboard::KEY::Home) {
                if (Keyboard::isKeyPressed(Keyboard::KEY::LShift) || Keyboard::isKeyPressed(Keyboard::KEY::RShift)) {
                    if (!hasTextSelected()) {
                        mStartSelect = mCursorPosition;
                    }

                    removeTextSelection();
                    // go to the first position on the string
                    setTextSelection(mStartSelect, 0);

                } else {
                    removeTextSelection();
                } // if  key pressed shift


                mCursorPosition = 0;
                mShowCursor     = true;
            }

            if (evt.key.code == Keyboard::KEY::End) {
                if (Keyboard::isKeyPressed(Keyboard::KEY::LShift) || Keyboard::isKeyPressed(Keyboard::KEY::RShift)) {
                    if (!hasTextSelected()) {
                        mStartSelect = mCursorPosition;
                    }

                    removeTextSelection();
                    setTextSelection(mStartSelect, mInputCommand.getSize());
                } else {
                    removeTextSelection();
                } // if  key pressed shift

                mCursorPosition = mInputCommand.getSize();
                mShowCursor     = true;
            }

            if (evt.key.code == Keyboard::KEY::Delete) {
                saveConsoleAction(mInputCommand, mCursorPosition);

                // if the cursor position its equals or more than 0 and
                // the cursor position is less the the buffer size
                // we can erase with no fear
                if (mCursorPosition < mInputCommand.getSize() && !hasTextSelected()) {
                    // erase at the cursor position
                    // since this is the delete key
                    mInputCommand.erase(mCursorPosition);
                    mShowCursor = true; // set the cursor to moving to get a better effect
                }

                if (hasTextSelected()) {
                    // remove all selected
                    int diffCursorPosition = mEndSelectionPosition - mStartSelectionPosition;
                    mShowCursor            = true;
                    mHasMadeAction         = true;

                    mInputCommand.erase(static_cast<int>(mStartSelectionPosition), static_cast<int>(diffCursorPosition));

                    mCursorPosition = mStartSelectionPosition;
                    removeTextSelection();
                } else {
                    // remove only one letter and remove text selection
                    removeTextSelection();
                }

                mInputText->setString(mInputCommand);
            }

        }


        // update the history position
        if (Keyboard::isKeyPressed(Keyboard::KEY::Up) && (mHasMadeAction == false || mInputCommand.getSize() == 0)) {
            // we add 1 to commandIndex to avoid going out of bounds
            if (mCommands.size() > 0 && mCommandIndex < mCommands.size()) {
                // if the command buffer is empty we show the first result of
                // our command history, otherwise we keep increment it
                if (mInputCommand != "" && (mCommandIndex + 1) < mCommands.size())  {
                    mCommandIndex++;
                }

                mInputCommand   = "";
                mCursorPosition = 0;

                saveConsoleAction(mInputCommand, mCursorPosition);
                mInputCommand.insert(mCursorPosition, mCommands[mCommandIndex]);
                mCursorPosition = mCommands[mCommandIndex].length();
            }

            removeTextSelection();
        }

        if (Keyboard::isKeyPressed(Keyboard::KEY::Down) && (mHasMadeAction == false || mInputCommand.getSize() == 0)) {
            if (mCommandIndex > 0) {
                mInputCommand   = "";
                mCursorPosition = 0;
                mCommandIndex--;

                if (mCommandIndex  < 0) {
                    mCommandIndex = 0;
                }

                saveConsoleAction(mInputCommand, mCursorPosition);
                mInputCommand.insert(mCursorPosition, mCommands[mCommandIndex]);
                mCursorPosition = mCommands[mCommandIndex].length();
            }

            removeTextSelection();
        }

        // update the cursor positions
        if (Keyboard::isKeyPressed(Keyboard::KEY::Left)) {
            // move the cursor per si
            if (mCursorPosition > 0) {
                mCursorPosition--;
                mShowCursor    = true;
                mHasMadeAction = true;
            } // if mCursorPosition > 0


            // handle the selection
            if (Keyboard::isKeyPressed(Keyboard::KEY::LShift) || Keyboard::isKeyPressed(Keyboard::KEY::RShift)) {
                if (!hasTextSelected()) {
                    mStartSelect = mCursorPosition + 1;
                }

                removeTextSelection();
                setTextSelection(mStartSelect, mCursorPosition);
            } else {
                if (hasTextSelected()) {
                    mCursorPosition = mStartSelectionPosition;
                }

                removeTextSelection();
            } // if  key pressed shift
            

        } // if key pressed left

        if (Keyboard::isKeyPressed(Keyboard::KEY::Right)) {
            if (mCursorPosition < mInputCommand.getSize()) {
                mCursorPosition++;
                mShowCursor    = true;
                mHasMadeAction = true;

            } // if mCursorPosition < mInputCommand.getSize()

            if (Keyboard::isKeyPressed(Keyboard::KEY::LShift) || Keyboard::isKeyPressed(Keyboard::KEY::RShift)) {
                if (!hasTextSelected()) {
                    mStartSelect = mCursorPosition - 1;
                }

                removeTextSelection();
                setTextSelection(mStartSelect, mCursorPosition);
            } else {
                if (hasTextSelected()) {
                    mCursorPosition = mEndSelectionPosition;
                }

                removeTextSelection();
            } // if  key pressed shift
        }

        if (Keyboard::isKeyPressed(Keyboard::KEY::Escape)) {
            // if the buffer have something we first clear it
            // after we just close the console
            if (mInputCommand.getSize() > 0) {
                saveConsoleAction(mInputCommand, mCursorPosition);
                mCursorPosition = 0;
                mInputCommand.clear();
                removeTextSelection();
            } else {
                // close the console if we dont have text on our input command area
                this->setVisible(false);    
            }
        }


        // scroll the content
        if (evt.type == Event::MouseWheelScrolled) {

            // if the scroll its vertical
            if(evt.mouseWheelScroll.wheel == Mouse::Wheel::VerticalWheel) {

                Vect2f pos = mOutputText->getPosition();
                // scroll up if delta == 1
                // scroll down if delta == -1
                if (evt.mouseWheelScroll.delta > 0 ) { // scroll up
                    if (pos.y <= mConsoleShape->getPosition().y) {
                        mHasScrolled = true;
                        calculateVisibleTextOutput(mCurrentOutputLine - 1);
                    }
                } else { // scroll down
                    if (mCurrentOutputLine < mOutputCommands.size()) {
                        mHasScrolled = true;
                        calculateVisibleTextOutput(mCurrentOutputLine + 1);
                    } else {
                        mHasScrolled = false;
                    }
                }
            }
        }

        if (evt.type == Event::TextEntered) {
            if (mShowKeyCode) {
                LOG << Log::VERBOSE
                    << "[LuaConsole::handleEvents] KeyCode: " << evt.text.unicode << std::endl;
            }


            // 13  = Carriage Return (Enter on Windows)
            // 10  = newline (Return MacOS)
            // 8   = backspace
            // 9   = tab
            // 27  = esc
            // 127 = Delete on Mac OS
            // 16 = Menu on Mac OS


            // This keys are only captured on Mac OS, Windows dont get this behaviour
            if (evt.text.unicode == 127 || evt.text.unicode == 16) {
                // do nothing

            } else if (evt.text.unicode == 13 || evt.text.unicode == 10) { // enter

                // if we have some command we execute it
                if (mInputCommand.getSize() > 0) {
                    // put on the screen the command
                    addMessage("Command: " + mInputCommand + "\n");
                    // call Lua
                    LuaAPI::script(mInputCommand);
                    mCommands.push_front(mInputCommand);

                    // Reset to the default text
                    mInputCommand   = "";
                    mCursorPosition = 0;
                    mCommandIndex   = 0;  // reset the index
                    // reset the action, so we can use 
                    // up and down to navigate through our command history
                    mHasMadeAction = false; 
                    removeTextSelection();
                }
            } else if (evt.text.unicode == 9) { // tab
                removeTextSelection();
                // Here we handle the tab
                // first get the command name
                static std::string cmd = mInputCommand.getString();
                static size_t cmdPos;

                // if we hade made an action we need to reparse our command to get
                // our new string
                if (mHasMadeAction) {
                    cmd = mInputCommand.getString();

                    // we can get the token from
                    // (window[TAB])
                    // )window[TAB]
                    // .window[TAB]
                    // 10*window[TAB] + / - * % & = ' "
                    // ->window[TAB]
                    
                    cmdPos = cmd.find_last_of("(). *>+-/&%=\"'", mCursorPosition - 1);

                    if (cmdPos == std::string::npos) {
                        cmdPos = 0;
                    } else {
                        cmdPos++;
                    }

                    cmd = cmd.substr(cmdPos, mCursorPosition - cmdPos);
                }

                // if the length if more/equals to 3 we try get the token
                if (cmd.length() >= 3) {

                    // get the result, it will be different if the command has not changed
                    String result = String(LuaExportAPI::getPredictions(cmd));

                    // if we get an hint
                    if (result.getSize() > 0) {
                        // tmp variable to hold the new cursor position
                        size_t newCursorPosition;

                        // remove the previus text typed (but keep the rest of the string)
                        mInputCommand.erase(cmdPos, mCursorPosition - cmdPos);
                        // get the new cursor position
                        newCursorPosition = cmdPos + result.getSize();
                        // add the new text
                        mInputCommand.insert(cmdPos, result);
                        // set the new cursor position
                        mCursorPosition = newCursorPosition;
                        mHasMadeAction  = false;
                    }
                }
                

            } else if (evt.text.unicode == 8) { // backspace
                // save the last command
                saveConsoleAction(mInputCommand, mCursorPosition);

                // if the cursor position its more than 0
                // we can erase with no fear
                if (mCursorPosition > 0 && !hasTextSelected()) {
                    // We remove the cursor position + cursor padding - 1
                    // thats means the lettler before the cursor
                    mInputCommand.erase(mCursorPosition - 1);
                    mCursorPosition--; // and decrese the cursor position
                    mShowCursor    = true; // set the cursor to moving to get a better effect
                    // we do have an action so the history will
                    // put the value on the cursor position
                    mHasMadeAction = true;
                }

                // if is text selected
                if (hasTextSelected()) {
                    // remove all selected
                    size_t diffCursorPosition = mEndSelectionPosition - mStartSelectionPosition;
                    mShowCursor               = true;
                    mHasMadeAction            = true;

                    mInputCommand.erase(static_cast<int>(mStartSelectionPosition), static_cast<int>(diffCursorPosition));
                    
                    // set the cursor position to the beginer of the selection
                    mCursorPosition = mStartSelectionPosition;
                    removeTextSelection();
                } else {
                    // remove only one letter and remove text selection
                    removeTextSelection();
                }
            } else if (evt.text.unicode == 27) { // esc
                // TODO(Pedro): Verify this on Windows and Linux
                // On MacOS the ESC event its not passed as TextEntered
                
            } else { // everything else
                saveConsoleAction(mInputCommand, mCursorPosition);

                // if is text selected
                if (hasTextSelected()) {
                    // remove all selected
                    size_t diffCursorPosition = mEndSelectionPosition - mStartSelectionPosition;
                    mShowCursor               = true;
                    mHasMadeAction            = true;

                    mInputCommand.erase(static_cast<int>(mStartSelectionPosition), static_cast<int>(diffCursorPosition));
                    
                    // set the cursor position to the beginer of the selection
                    mCursorPosition = mStartSelectionPosition;
                    removeTextSelection();
                } else {
                    // remove only one letter and remove text selection
                    removeTextSelection();
                }

                // 40  = (
                // 41  = )
                // 91  = [
                // 93  = ]
                // 123 = {
                // 125 = }
                // Auto complete the parenteses brackets and stuff
                // if we are on the end of the file
                if (mCursorPosition == mInputCommand.getSize()) {
                    if (evt.text.unicode == 40) {
                        mInputCommand.insert(mCursorPosition, ")");
                    } else if (evt.text.unicode == 91) {
                        mInputCommand.insert(mCursorPosition, "]");
                    } else if (evt.text.unicode == 123) {
                        mInputCommand.insert(mCursorPosition, "}");
                    }
                } // if mCursorPosition == mInputCommand.getSize() - 1

                // nice parenteses auto-complete feature
                // since we always put both parenteses we check if we are trying to type
                if ((evt.text.unicode == 41 && mLastChar == 40)
                    || (evt.text.unicode == 93 && mLastChar == 91)
                    || (evt.text.unicode == 125 && mLastChar == 123)) {
                    // we just update the cursor position
                    mCursorPosition++;
                } else {
                    // just put the char to the buffer if it's not
                    mInputCommand.insert(mCursorPosition, evt.text.unicode);
                    // increase the cursor position since we just added another lettler
                    mCursorPosition++;
                    // we do have an action so the history will
                    // put the value on the cursor position
                    mHasMadeAction = true;
                }

            } // if not any of the unicodes
            // save the last char typed
            mLastChar = evt.text.unicode;
        } // if event text entered
        // set the string to the text
        mInputText->setString(mInputCommand);

        // update the position of the input text 
        updateInputText();
    } // if console is visible
}

void LuaConsole::addMessageStd(const std::string& message) {
    this->addMessage(String(message));
}

void LuaConsole::addMessage(const String& message) {
    // fix problems with \n been passed to the string
    String messageTmp(message);
    
    messageTmp.removeNewLine();
    messageTmp.removeCarriageReturn();

    mOutputCommands.push_back(messageTmp);

    // set the string on the mOutputTextDraw
    if(isVisible()) {
        if (!mHasScrolled) {
            calculateVisibleTextOutput();
        }
    }
}

void LuaConsole::calculateVisibleTextOutput(const int& lineNumber) {
    // default go to bottom
    if (lineNumber == -1) {
        mCurrentOutputLine = mOutputCommands.size();
    } else {
        mCurrentOutputLine = lineNumber;    
    }

    // make sure we are on our vector bounds
    if (lineNumber >= mOutputCommands.size()) {
        mCurrentOutputLine = mOutputCommands.size();
    }

    if (lineNumber < 1 && lineNumber != -1) {
        mCurrentOutputLine = 0;
    }

    int offsetStart = 0;

    // if the line number is bigger we make an offset
    if (mCurrentOutputLine > mMaxNumberLines) {
        offsetStart = mCurrentOutputLine - mMaxNumberLines;
    }

    // if the offset is at zero we dont need to change the 
    // currentOutputLine so we add 1 again (on the call we do -1)
    if (offsetStart == 0) {
        mCurrentOutputLine = lineNumber + 1;
    }

    std::string tmp;
    for(int i = offsetStart; i < mCurrentOutputLine; i++) {
        tmp = tmp + mOutputCommands[i].getString();
    }

    mOutputText->setString(String(tmp));
}

void LuaConsole::setTextSelection(const size_t& start, const size_t& end) {
    Vect2f tmpCursorPosition = mInputText->getPosition();
    tmpCursorPosition.y      = mCursorShape->getPosition().y;

    float diffCursorPosition = 0;

    if (end < start) {
        diffCursorPosition      = start - end;
        tmpCursorPosition.x     = tmpCursorPosition.x + (end * mFontWidth);
        mStartSelectionPosition = end;
        mEndSelectionPosition   = start;
    } else {
        diffCursorPosition      = end - start;
        tmpCursorPosition.x     = tmpCursorPosition.x + (start * mFontWidth);
        mStartSelectionPosition = start;
        mEndSelectionPosition   = end;
    }
    
    mSelectedShape->setPosition(tmpCursorPosition);

    Vect2f sizeSelectedText = mSelectedShape->getSize();
    sizeSelectedText.x      = diffCursorPosition * mFontWidth;
    mSelectedShape->setSize(sizeSelectedText);

    mIsTextSelected = true;
}

void LuaConsole::removeTextSelection() {
    mIsTextSelected         = false;
    Vect2f sizeSelectedText = mSelectedShape->getSize();
    sizeSelectedText.x      = 0.0f;
    mSelectedShape->setSize(sizeSelectedText);
}

bool LuaConsole::hasTextSelected() {
    return mIsTextSelected;
}

void LuaConsole::registerEngine(MedievalEngine* engine) {
    mResources  = engine->getResourceManager();
    mWindowSize = engine->getWindow()->getSize();

    // we se the window size a little bit smaller than the full window size
    mConsoleSize.x = static_cast<int>(mWindowSize.x * 0.98f);
    mConsoleSize.y = static_cast<int>(mWindowSize.y * 0.98f);

    // add some margin's to our console window
    mMargin.x = mWindowSize.x * 0.01f;
    mMargin.y = mWindowSize.y * 0.01f;


    // our resources id's
    ResourceID inputTextID;
    ResourceID outputTextID;
    ResourceID consoleShapeID;
    ResourceID inputLineShapeID;
    ResourceID selectedShapeID;
    ResourceID cursorShapeID;
    ResourceID fontID;

    // set the monospace font for our console
    // TODO(Pedro): Move this font to a dat file
    fontID = mResources->loadFont("system/Hack-Regular.ttf");

    outputTextID = inputTextID = mResources->createText(String(""), Window::fontSize(0.20f), fontID);
    mOutputText  = mResources->getResource<Text>(outputTextID);

    mFontHeight = mOutputText->getFontHeight(Window::fontSize(0.20f));

    inputTextID = mResources->createText(mInputCommand, Window::fontSize(0.25f), fontID);
    mInputText  = mResources->getResource<Text>(inputTextID);

    // before we set the buffer, lets get the character font width and height
    // this will work only with monospace fonts
    mInputText->setString(String("A"));
    mFontWidth = mInputText->getSize().x;

    // to get a line with a little bit of padding we multiply 
    // the size of the text input by two
    mLineHeight = mInputText->getSize().y * 2;

    // calcule max terminal line number
    mMaxNumberLines = (mConsoleSize.y + (mLineHeight / 2)) / mFontHeight;

    // reset the input text
    mInputText->setString(String(""));

    consoleShapeID = mResources->createShape(mConsoleSize, mBackgroundColor, mMargin);
    mConsoleShape  = mResources->getResource<Shape>(consoleShapeID);

    mOutputText->setPosition(Vect2f(mConsoleShape->getPosition().x, mConsoleShape->getPosition().y - mLineHeight));

    inputLineShapeID = mResources->createShape(Vect2f(static_cast<float>(mConsoleSize.x),  mLineHeight), mBackgroundColor);
    mInputLineShape  = mResources->getResource<Shape>(inputLineShapeID);

    mInputLineShape->setPosition(Vect2f(mConsoleShape->getPosition().x, mConsoleShape->getPosition().y + mConsoleShape->getSize().y - mLineHeight));
    mInputText->setPosition(mInputLineShape->getPosition());

    Area consoleShapeArea   = mConsoleShape->getGlobalBounds();
    consoleShapeArea.height = consoleShapeArea.height - mLineHeight;

    // set the shape height for our cursor to be 80% of the size
    float cursorSize = mLineHeight * 0.80f;
    Vect2f cursorPos = mInputLineShape->getPosition();
    // add a padding to the cursor, to make it align on vertically on center
    cursorPos.y = cursorPos.y + (mLineHeight * 0.10f);

    cursorShapeID = mResources->createShape(Vect2f(1.5f, cursorSize), Color(255, 255, 255));
    mCursorShape  = mResources->getResource<Shape>(cursorShapeID);
    mCursorShape->setPosition(cursorPos);

    selectedShapeID = mResources->createShape(Vect2f(0.f, cursorSize), Color(53, 171, 255, 153));
    mSelectedShape  = mResources->getResource<Shape>(selectedShapeID);
    mSelectedShape->setPosition(Vect2f(cursorPos.x, cursorPos.y));


    // Define this call as an observer from the log
    LOG_OBJECT->setObserver(this);
}

void LuaConsole::draw(Window& window) {

    Vect2f cursorShapePos = mCursorShape->getPosition();
    cursorShapePos.x      = mInputText->getPosition().x + (mCursorPosition * mFontWidth);

    mCursorShape->setPosition(cursorShapePos);


    window.draw(mConsoleShape);
    window.draw(mInputLineShape);

    Area consoleShapeArea   = mConsoleShape->getGlobalBounds(); 
    consoleShapeArea.height = consoleShapeArea.height - mLineHeight;

    Area consoleArea(consoleShapeArea.left / mWindowSize.x,
                            (consoleShapeArea.top) / mWindowSize.y,
                            (consoleShapeArea.width) / mWindowSize.x,
                            (consoleShapeArea.height) / mWindowSize.y);

    RenderArea consoleRenderArea;

    consoleRenderArea.reset(Area(consoleShapeArea.left, consoleShapeArea.top,
                                  consoleShapeArea.width, consoleShapeArea.height));

    consoleRenderArea.setViewArea(consoleArea);

    window.setRenderArea(consoleRenderArea);

    window.draw(mOutputText);

    window.resetViewState();

    Area inputLineBackgroundArea = mInputLineShape->getGlobalBounds();
    Area lineEditArea(inputLineBackgroundArea.left / mWindowSize.x,
                            inputLineBackgroundArea.top / mWindowSize.y,
                            inputLineBackgroundArea.width / mWindowSize.x,
                            inputLineBackgroundArea.height / mWindowSize.y);

    RenderArea inputLineRenderArea;

    inputLineRenderArea.reset(Area(inputLineBackgroundArea.left, inputLineBackgroundArea.top,
                                  inputLineBackgroundArea.width, inputLineBackgroundArea.height));
    inputLineRenderArea.setViewArea(lineEditArea);

    window.setRenderArea(inputLineRenderArea);

    // background text selection
    window.draw(mSelectedShape);
    // text
    window.draw(mInputText);

    window.resetViewState();

    if (!mCursorBlinking || mShowCursor == true) {
        window.draw(mCursorShape);
    }
    
    MEUInt32 cursorBlinkTime = mCusorBlinkTime;

    // if we are moving the cursor we add a padding to the time
    if (mShowCursor) {
        cursorBlinkTime = cursorBlinkTime + 500;
    }

    // we do this calculantion on the end, so we can get a better visual effect on the selection text on console
    if (mClockCursorBlinking.getMilliSeconds() > cursorBlinkTime) {
        if (mCursorBlinking == true && mShowCursor == false) {
            mCursorBlinking = false;
        } else {
            mCursorBlinking = true;
        }

        mClockCursorBlinking.restart();

        // set the cursor moving to false to get a smoth effect
        mShowCursor = false;
    }
}

bool LuaConsole::isVisible() {
    return mIsConsoleVisible;
}

void LuaConsole::setVisible(bool visible) {
    mIsConsoleVisible = visible;

    if (visible == false) {
        mHasScrolled = false;
        calculateVisibleTextOutput();
    }
}

LuaConsole::~LuaConsole() {
    // TODO(Pedro): make some test about memory
    // we cant delete the pointers here for some reason
}