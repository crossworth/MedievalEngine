#include "LuaConsole.h"
#include "Engine/MedievalEngine.h"
#include "Helper/Clipboard.h"

using namespace ME;


LuaConsole::LuaConsole() {
    mIsVisible      = false;
    mBuffer         = "";
    cmdBuffer       = "";
    mLastChar       = 0;
    mFontLetterSize = 0;
    mText           = nullptr;
    mOutput         = nullptr;
    mBG             = nullptr;
    mLineEdit       = nullptr;
    mSelectedText   = nullptr;
    mShapeCursor    = nullptr;
    mBGColor        = Color(0, 0, 0, 120);
    mCursorMoving   = false;
    mHasScrolled    = false;
    mCursorBlinking = false;
    mDebugKeyCodes  = false;
    mHasMakeAction  = false;
    mStepScroll     = 30;
    mCursorPosition = 0;
    mCommandsIndex  = 0;
    mCusorBlinkTime = 500;

    mClockBlinkCursor.restart();

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
    
}

void LuaConsole::setShowUnicodeKeyCodes(bool debug) {
    mDebugKeyCodes = debug;
}

void LuaConsole::handleEvents(Event& evt) {
    if (evt.type == Event::KeyPressed) {

        if (KeyMapper::action("toggle_console", evt)) {
            if (isVisible()) {
                setVisible(false);
            } else {
                setVisible(true);
            }
        }
    }

    // handle the key's on the window
    if(isVisible()) {
        if (evt.type == Event::KeyPressed) {

            // Control + V
            if (evt.key.code == Keyboard::KEY::V && 
                ((evt.key.control && !OS::isMacOS()) || (evt.key.system && OS::isMacOS()))) {
                std::string text = Clipboard::getData();
                mBuffer.insert(mCursorPosition, text);
                mCursorPosition = mCursorPosition + text.size();
            }

            if (evt.key.code == Keyboard::KEY::Home) {
                mCursorPosition = 0;
            }

            if (evt.key.code == Keyboard::KEY::End) {
                mCursorPosition = mBuffer.getSize();
            }

            if (evt.key.code == Keyboard::KEY::Delete) {
                // if the cursor position its equals or more than 0 and
                // the cursor position is less the the buffer size
                // we can erase with no fear
                if (mCursorPosition > 0 && mCursorPosition < mBuffer.getSize()) {
                    // erase at the cursor position
                    // since this is the delete key
                    mBuffer.erase(mCursorPosition);
                    mCursorMoving = true; // set the cursor to moving to get a better effect
                    // there no need to invalidade the cmdbuffer since we just deleting
                    mText->setString(mBuffer);
                }
            }

        }


        // update the history position
        if (Keyboard::isKeyPressed(Keyboard::KEY::Up)) {
            if (mCommands.size() > 0 && mCommandsIndex < mCommands.size()) {
                if (mHasMakeAction == false) {
                    mBuffer         = "";
                    mCursorPosition = 0;
                }

                mBuffer.insert(mCursorPosition, mCommands[mCommandsIndex]);
                mCursorPosition = mCommands[mCommandsIndex].length();
                cmdBuffer = ""; // invalidate the command Buffer
                mCommandsIndex++;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::KEY::Down)) {
            if (mCommandsIndex > 0) {
                if (mHasMakeAction == false) {
                    mBuffer         = "";
                    mCursorPosition = 0;
                }

                mCommandsIndex--;
                if (mCommandsIndex < 0) {
                    mCommandsIndex = 0;
                }

                mBuffer.insert(mCursorPosition, mCommands[mCommandsIndex]);
                mCursorPosition = mCommands[mCommandsIndex].length();
                cmdBuffer = ""; // invalidate the command Buffer
            }
        }

        // update the cursor positions
        if (Keyboard::isKeyPressed(Keyboard::KEY::Left)) {
            if (mCursorPosition > 0) {
                mCursorPosition--;
                mCursorMoving  = true;
                cmdBuffer      = ""; // invalidate the command Buffer
                mHasMakeAction = true;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::KEY::Right)) {
            if (mCursorPosition < mBuffer.getSize()) {
                mCursorPosition++;
                mCursorMoving  = true;
                cmdBuffer      = ""; // invalidate the command Buffer
                mHasMakeAction = true;


                Vect2f sizeSelectedText = mSelectedText->getSize();
                sizeSelectedText.x = sizeSelectedText.x + mFontLetterSize;
                mSelectedText->setSize(sizeSelectedText);
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::KEY::Escape)) {
            // if the buffer have something we first clear it
            // after we just close the console
            if (mBuffer.getSize() > 0) {
                mBuffer.clear();
                mCursorPosition = 0;
            } else {
                // close the console
                this->setVisible(false);    
            }
        }


        // scroll the content
        if (evt.type == Event::MouseWheelScrolled) {

            // if the scroll its vertical
            if(evt.mouseWheelScroll.wheel == Mouse::Wheel::VerticalWheel) {

                Vect2f pos = mOutput->getPosition();
                // scroll up if delta == 1
                // scroll down if delta == -1
                if (evt.mouseWheelScroll.delta > 0 ) { // scroll up
                    if (pos.y <= mBG->getPosition().y) {
                        mHasScrolled = true;

                        mOutput->setPosition(Vect2f(mBG->getPosition().x, mOutput->getPosition().y  + mStepScroll));
                    }
                } else { // scroll down
                    if (pos.y + mOutput->getSize().y + mLineHeight >= mBG->getPosition().y + mBG->getSize().y ) {
                        mHasScrolled = true;
                        mOutput->setPosition(Vect2f(mBG->getPosition().x, mOutput->getPosition().y  - mStepScroll));
                    } else {
                        mHasScrolled = false;
                    }
                }
            }
        }

        if (evt.type == Event::TextEntered) {
            if (mDebugKeyCodes) {
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
                if (mBuffer.getSize() > 0) {
                    // put on the screen the command
                    addMessage("Command: " + mBuffer + "\n");
                    // call Lua
                    LuaAPI::script(mBuffer);
                    mCommands.push_front(mBuffer);

                    // Reset to the default text
                    mBuffer         = "";
                    mCursorPosition = 0;
                    cmdBuffer       = ""; // invalidate the command Buffer
                    mCommandsIndex  = 0;  // rest the index
                    mHasMakeAction = false; // reset the make action
                }
            } else if (evt.text.unicode == 9) { // tab
                // Here we handle the tab
                // first get the command name
                std::string cmd = mBuffer.getString();

                // we can get the token from
                // (window[TAB])
                // )window[TAB]
                // .window[TAB]
                // 10*window[TAB] + / - * % & = ' "
                // ->window[TAB]
                size_t cmdPos;
                cmdPos = cmd.find_last_of("(). *>+-/&%=\"'", mCursorPosition - 1);

                if (cmdPos == std::string::npos) {
                    cmdPos = 0;
                } else {
                    cmdPos++;
                }

                cmd = cmd.substr(cmdPos, mCursorPosition - cmdPos);

                // if the length if more/equals to 3 we try get the token
                if (cmd.length() >= 3) {

                    if (cmdBuffer == "") {
                        cmdBuffer =  cmd;
                    }

                    // save the result hint
                    String result = String(LuaExportAPI::getPredictions(cmdBuffer));

                    // if we get an hint
                    if (result.getSize() > 0) {
                        // tmp variable to hold the new cursor position
                        size_t newCursorPosition;

                        // remove the previus text typed (but keep the rest of the string)
                        mBuffer.erase(cmdPos, mCursorPosition - cmdPos);
                        // get the new cursor position
                        newCursorPosition = cmdPos + result.getSize();
                        // add the new text
                        mBuffer.insert(cmdPos, result);
                        // set the new cursor position
                        mCursorPosition = newCursorPosition;
                    }
                }

                // we do have an action so the history will
                // put the value on the cursor position
                mHasMakeAction = true;
            } else if (evt.text.unicode == 8) { // backspace
                // if the cursor position its more than 0
                // we can erase with no fear
                if (mCursorPosition > 0) {
                    // We remove the cursor position + cursor padding - 1
                    // thats means the lettler before the cursor
                    mBuffer.erase(mCursorPosition - 1);
                    mCursorPosition--; // and decrese the cursor position
                    mCursorMoving  = true; // set the cursor to moving to get a better effect
                    cmdBuffer      = ""; // invalidate the command Buffer
                    // we do have an action so the history will
                    // put the value on the cursor position
                    mHasMakeAction = true;
                }
            } else if (evt.text.unicode == 27) { // esc
                // TODO(Pedro): Verify this on Windows, Linux
                // On MacOS the ESC event its not passed as TextEntered
                
            } else { // everything else
                
                // 40  = (
                // 41  = )
                // 91  = [
                // 93  = ]
                // 123 = {
                // 125 = }
                // Auto complete the parenteses brackets and stuff
                // if we are on the end of the file
                if (mCursorPosition == mBuffer.getSize()) {
                    if (evt.text.unicode == 40) {
                        mBuffer.insert(mCursorPosition, ")");
                    } else if (evt.text.unicode == 91) {
                        mBuffer.insert(mCursorPosition, "]");
                    } else if (evt.text.unicode == 123) {
                        mBuffer.insert(mCursorPosition, "}");
                    }
                } // if mCursorPosition == mBuffer.getSize() - 1

                // nice parenteses auto-complete feature
                // since we always put both parenteses we check if we are trying to type
                if ((evt.text.unicode == 41 && mLastChar == 40)
                    || (evt.text.unicode == 93 && mLastChar == 91)
                    || (evt.text.unicode == 125 && mLastChar == 123)) {
                    // we just update the cursor position
                    mCursorPosition++;
                } else {
                    // just put the char to the buffer if it's not
                    mBuffer.insert(mCursorPosition, evt.text.unicode);
                    // increase the cursor position since we just added another lettler
                    mCursorPosition++;
                    cmdBuffer       = ""; // invalidate the command Buffer
                    // we do have an action so the history will
                    // put the value on the cursor position
                    mHasMakeAction = true;
                }


            } // if not any of the unicodes
            // save the last char typed
            mLastChar = evt.text.unicode;
        } // if event text entered
        // set the string to the text
        mText->setString(mBuffer);
    } // if console is visible
}


void LuaConsole::addMessageStd(const std::string& buffer) {
    this->addMessage(String(buffer));
}

void LuaConsole::addMessage(const String& buffer) {
    mBufferOutput = mBufferOutput + buffer;
}

void LuaConsole::registerEngine(MedievalEngine* engine) {
    mResources  = engine->getResourceManager();
    mWindowSize = engine->getWindow()->getSize();

    // we se the window size a little bit less than the full window size
    mConsoleSize.x = static_cast<int>(mWindowSize.x * 0.98f);
    mConsoleSize.y = static_cast<int>(mWindowSize.y * 0.98f);

    // add some margin's to our console window
    mMargin.x = mWindowSize.x * 0.01f;
    mMargin.y = mWindowSize.y * 0.01f;

    ResourceID textID;
    ResourceID outputID;
    ResourceID bgID;
    ResourceID lineEditID;
    ResourceID selectedTextID;
    ResourceID fontID;
    ResourceID textCursorID;

    // set the monospace font for our console
    // TODO(Pedro): Move this font to a dat file
    fontID = mResources->loadFont("system/Hack-Regular.ttf");

    outputID = textID = mResources->createText(String(""), Window::fontSize(0.20f), fontID);
    mOutput  = mResources->getResource<Text>(outputID);

    textID = mResources->createText(mBuffer, Window::fontSize(0.25f), fontID);
    mText  = mResources->getResource<Text>(textID);

    // before we set the buffer, lets get the character font width and height
    mText->setString(String("A"));
    mFontLetterSize = mText->getSize().x;

    // MAGIC NUMBER HERE! for some reason we have to multiply the text size
    // by 2 for get the right size of the height
    mLineHeight = mText->getSize().y * 2;

    mText->setString(String(""));

    bgID = mResources->createShape(mConsoleSize, mBGColor, mMargin);
    mBG  = mResources->getResource<Shape>(bgID);

    lineEditID = mResources->createShape(Vect2f(static_cast<float>(mConsoleSize.x),  mLineHeight), mBGColor);
    mLineEdit  = mResources->getResource<Shape>(lineEditID);

    mLineEdit->setPosition(Vect2f(mBG->getPosition().x, mBG->getPosition().y + mBG->getSize().y - mLineHeight));
    mText->setPosition(mLineEdit->getPosition());


    Area mBGArea   = mBG->getGlobalBounds();
    mBGArea.height = mBGArea.height - mLineHeight;

    // set the shape height for our cursor to be 80% of the size
    float cursorSize = mLineHeight * 0.80f;
    Vect2f cursorPos = mLineEdit->getPosition();
    // add a padding to the cursor, to make it align on vertically on center
    cursorPos.y = cursorPos.y + (mLineHeight * 0.10f);

    textCursorID = mResources->createShape(Vect2f(1.5f, cursorSize), Color(255, 255, 255));
    mShapeCursor = mResources->getResource<Shape>(textCursorID);
    mShapeCursor->setPosition(cursorPos);

    selectedTextID = mResources->createShape(Vect2f(0.f, cursorSize), Color(53, 171, 255, 153));
    mSelectedText  = mResources->getResource<Shape>(selectedTextID);
    mSelectedText->setPosition(Vect2f(cursorPos.x, cursorPos.y));



    // Get the messages from the log
    LOG_OBJECT->setObserver(this);
}

void LuaConsole::draw(Window& window) {

    if (mClockBlinkCursor.getMilliSeconds() > mCusorBlinkTime) {
        if (mCursorBlinking == true && mCursorMoving == false) {
           mCursorBlinking = false;
        } else {
            mCursorBlinking = true;
        }

        mClockBlinkCursor.restart();

        // set the cursor moving to false to get a smoth effect
        mCursorMoving = false;
    }

    float lineTextWidth = mText->getSize().x;

    if ((lineTextWidth + mFontLetterSize) >= mLineEdit->getSize().x) {
        float lineDiff     = (lineTextWidth + mFontLetterSize)  - mLineEdit->getSize().x;
        Vect2f lineEditPos = mLineEdit->getPosition();
        lineEditPos.x      = lineEditPos.x - lineDiff;
        mText->setPosition(lineEditPos);
    } else {
        mText->setPosition(mLineEdit->getPosition());
    }


    Vect2f mShapeCursorPos = mShapeCursor->getPosition();
    mShapeCursorPos.x      = mText->getPosition().x + (mCursorPosition * mFontLetterSize);

    mShapeCursor->setPosition(mShapeCursorPos);


    window.draw(mBG);
    window.draw(mLineEdit);
    window.draw(mSelectedText);
    

    Area mBGArea   = mBG->getGlobalBounds();
    mBGArea.height = mBGArea.height - mLineHeight;

    sf::FloatRect panelRect(mBGArea.left / mWindowSize.x,
                            (mBGArea.top) / mWindowSize.y,
                            (mBGArea.width) / mWindowSize.x,
                            (mBGArea.height) / mWindowSize.y);

    panelView.reset(sf::FloatRect(mBGArea.left, mBGArea.top,
                                  mBGArea.width, mBGArea.height));

    panelView.setViewport(panelRect);

    window.getWindowPtr()->setView(panelView);

    mOutput->setString(mBufferOutput);

    // if we dont have scrolled yet we will automatic update the ouput position
    if (mHasScrolled == false) {
        mOutput->setPosition(Vect2f(mBG->getPosition().x, mConsoleSize.y - mOutput->getSize().y - mLineHeight));
    }

    window.draw(mOutput);
    window.getWindowPtr()->setView(window.getWindowPtr()->getDefaultView());



    Area mLineEditArea = mLineEdit->getGlobalBounds();
    sf::FloatRect panelRectLineEdit(mLineEditArea.left / mWindowSize.x,
                            mLineEditArea.top / mWindowSize.y,
                            mLineEditArea.width / mWindowSize.x,
                            mLineEditArea.height / mWindowSize.y);


    panelView.reset(sf::FloatRect(mLineEditArea.left, mLineEditArea.top,
                                  mLineEditArea.width, mLineEditArea.height));
    panelView.setViewport(panelRectLineEdit);

    window.getWindowPtr()->setView(panelView);

    window.draw(mText);

    window.getWindowPtr()->setView(window.getWindowPtr()->getDefaultView());
 

    if (!mCursorBlinking) {
        window.draw(mShapeCursor);
    }

}

bool LuaConsole::isVisible() {
    return mIsVisible;
}

void LuaConsole::setVisible(bool visible) {
    mIsVisible = visible;

    if (visible == false) {
        mHasScrolled = false;
        mOutput->setPosition(Vect2f(mBG->getPosition().x, mConsoleSize.y - mOutput->getSize().y - mLineHeight));
    }
}

LuaConsole::~LuaConsole() {
    // TODO(Pedro): make some test about memory
    // we cant delete the pointers here for some reason
}