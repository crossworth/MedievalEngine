#include "LuaConsole.h"
#include "Engine/MedievalEngine.h"

using namespace ME;


LuaConsole::LuaConsole() {
    mIsVisible      = false;
    mCursor         = sf::String("|");
    mDefaultText    = sf::String("CMD:");
    mBuffer         = mDefaultText;
    cmdBuffer       = "";
    mText           = nullptr;
    mOutput         = nullptr;
    mBG             = nullptr;
    mLineEdit       = nullptr;
    mBGColor        = Color(0, 0, 0, 120);
    mNumberLines    = 1;
    mCusorBlinkTime = 500;
    mCursorMoving   = false;
    mHasScrolled    = false;
    mStepScroll     = 30;
    mCursorPosition = 0;
    mCommandsIndex  = 0;
    mHasMakeAction  = 0;

    mCursorPadding = mDefaultText.getSize();

    mClockBlinkCursor.restart();
}

std::string LuaConsole::getToken(const std::string& cmd) {
    return std::string("");

}

void LuaConsole::handleEvents(Event& evt) {
    if (evt.type == Event::KeyPressed) {

        if (evt.key.code == Keyboard::KEY::F3) {
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

            if (evt.key.code == Keyboard::KEY::Home) {
                mCursorPosition = 0;
            }

            if (evt.key.code == Keyboard::KEY::End) {
                mCursorPosition = mBuffer.getSize() - mCursorPadding;
            }

            if (evt.key.code == Keyboard::KEY::Delete) {
                // if the cursor position its equals or more than 0 and
                // the cursor position is less the the buffer size
                // we can erase with no fear
                if (mCursorPosition >= 0 && mCursorPosition + mCursorPadding < mBuffer.getSize()) { 
                    // erase at the cursor position
                    // since this is the delete key
                    mBuffer.erase(mCursorPosition + mCursorPadding);
                    mCursorMoving = true; // set the cursor to moving to get a better effect
                    // there no need to invalidade the cmdbuffer since we just deleting
                }
            }

        }

        // update the history position
        if (Keyboard::isKeyPressed(Keyboard::KEY::Up)) {
            if (mCommands.size() > 0 && mCommandsIndex < mCommands.size()) {
                if (mHasMakeAction == false) {
                    mBuffer         = mDefaultText;
                    mCursorPosition = 0;
                }

                mBuffer.insert(mCursorPadding + mCursorPosition, mCommands[mCommandsIndex]);
                mCursorPosition = mCommands[mCommandsIndex].length();
                cmdBuffer = ""; // invalidate the command Buffer
                mCommandsIndex++;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::KEY::Down)) {
            if (mCommandsIndex > 0) {
                if (mHasMakeAction == false) {
                    mBuffer         = mDefaultText;
                    mCursorPosition = 0;
                }

                mCommandsIndex--;
                if (mCommandsIndex < 0) {
                    mCommandsIndex = 0;
                }

                mBuffer.insert(mCursorPadding + mCursorPosition, mCommands[mCommandsIndex]);
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
            if (mCursorPosition + mCursorPadding < mBuffer.getSize()) {
                mCursorPosition++;
                mCursorMoving  = true;
                cmdBuffer      = ""; // invalidate the command Buffer
                mHasMakeAction = true;
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
             // 13 = newline (ENTER)
             // 8  = backspace
             // 9  = tab
             // 27 = esc
            if (evt.text.unicode == 13) { // enter
                // Remove the CMD: from the start of the string
                mBuffer.erase(0, mCursorPadding);

                // if we have some command we execute it
                if (mBuffer.getSize() > 0) {
                    // put on the screen the command 
                    addMessage("COMMAND: " + mBuffer + "\n");
                    // call Lua 
                    LuaAPI::script(mBuffer);
                    mCommands.push_front(mBuffer);

                    // Reset to the default text
                    mBuffer         = mDefaultText;
                    mCursorPosition = 0;
                    cmdBuffer       = ""; // invalidate the command Buffer
                    mCommandsIndex  = 0;  // rest the index
                    mHasMakeAction = false; // reset the make action
                }
            } else if (evt.text.unicode == 9) { // tab
                // Here we handle the tab
                // first get the command name
                std::string cmd = mBuffer.toAnsiString();
                // remove the CMD: from the start to get the real command
                cmd.erase(0, mCursorPadding);

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
                    
                    // store the result hint
                    sf::String result = sf::String(LuaFunctions::autoComplete(cmdBuffer));

                    // if we get an hint
                    if (result.getSize() > 0) {
                        // tmp variable to hold the new cursor position
                        size_t newCursorPosition;

                        // remove the previus text typed (but keep the rest of the string)
                        mBuffer.erase(mCursorPadding + cmdPos, mCursorPosition - cmdPos);
                        // get the new cursor position 
                        newCursorPosition = cmdPos + result.getSize();
                        // add the new text
                        mBuffer.insert(mCursorPadding + cmdPos, result);
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
                    mBuffer.erase(mCursorPosition + mCursorPadding - 1);
                    mCursorPosition--; // and decrese the cursor position
                    mCursorMoving  = true; // set the cursor to moving to get a better effect
                    cmdBuffer      = ""; // invalidate the command Buffer
                    // we do have an action so the history will
                    // put the value on the cursor position
                    mHasMakeAction = true; 
                }
            } else if (evt.text.unicode == 27) { // esc
                // do nothing
                

            } else { // everything else
                // just put the char to the buffer if it's not 
                mBuffer.insert(mCursorPosition + mCursorPadding, evt.text.unicode);
                // increase the cursor position since we just added another lettler
                mCursorPosition++;
                cmdBuffer       = ""; // invalidate the command Buffer
                // we do have an action so the history will
                // put the value on the cursor position
                mHasMakeAction = true;
            }

            // set the string to the text
            mText->setString(mBuffer);
        }   
    }
}


void LuaConsole::addMessage(const sf::String& buffer) {
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
    ResourceID fontID;

    // set the monospace font for our console
    fontID = mResources->loadFont("system/Inconsolata.ttf");
    
    outputID = textID = mResources->createText(sf::String(""), Window::fontSize(0.20f), fontID);
    mOutput  = mResources->getResource<Text>(outputID);

    textID = mResources->createText(mBuffer, Window::fontSize(0.25f), fontID);
    mText  = mResources->getResource<Text>(textID);
    // MAGIC NUMBER WHERE! for some reason we have to multiply the text size
    // by 2 for get the right size of the height
    mLineHeight = mText->getSize().y * 2; 
    mText->setString(mBuffer);
    mNumberLines = 1;

    bgID = mResources->createShape(mConsoleSize, mBGColor, mMargin);
    mBG  = mResources->getResource<Shape>(bgID);

    lineEditID = mResources->createShape(Vect2f(static_cast<float>(mConsoleSize.x),  mLineHeight), mBGColor);
    mLineEdit  = mResources->getResource<Shape>(lineEditID);

    mLineEdit->setPosition(Vect2f(mBG->getPosition().x, mBG->getPosition().y + mBG->getSize().y - mLineHeight));
    mText->setPosition(mLineEdit->getPosition());  

    Area mBGArea   = mBG->getGlobalBounds();
    mBGArea.height = mBGArea.height - mLineHeight;

    
    // Get the messages from the log
    LOG_OBJECT->setObserver(this);
}

void LuaConsole::draw(Window& window) {

    if (mClockBlinkCursor.getMilliSeconds() > mCusorBlinkTime) {
        // we only change to space if we are not moving the cursor
        if (mCursor == "|" && mCursorMoving == false) {
            mCursor = " ";
        } else {
            mCursor = "|";
        }

        mClockBlinkCursor.restart();

        // set the cursor moving to false to get a smote effect
        mCursorMoving = false;
    }


    // create a tmp buffer to hold our string with the command and the cursor
    sf::String cursorBuffer = mBuffer;
    // insert the cursor into the position
    cursorBuffer.insert(mCursorPosition + mCursorPadding, mCursor);
    mText->setString(cursorBuffer);


    window.draw(mBG);
    window.draw(mLineEdit);

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

    window.draw(mText);
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
