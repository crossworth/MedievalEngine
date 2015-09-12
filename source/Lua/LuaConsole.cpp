#include "LuaConsole.h"
#include "Engine/MedievalEngine.h"

using namespace ME;


LuaConsole::LuaConsole() {
    mIsVisible      = false;
    mCursor         = sf::String("|");
    mDefaultText    = sf::String("CMD:");
    cmd_check       = sf::String("");
    mBuffer         = mDefaultText;
    mText           = nullptr;
    mOutput         = nullptr;
    mBG             = nullptr;
    mLineEdit       = nullptr;
    mBGColor        = Color(0, 0, 0, 120);
    mNumberLines    = 1;
    mCusorBlinkTime = 500;
    mHasScrolled    = false;
    mStepScroll     = 30;

    mClockBlinkCursor.restart();
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

    if(isVisible()) {

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
            if (evt.text.unicode == 13) {
                // Remove the CMD: from the start of the string
                mBuffer.erase(0, 4);

                // if we have some command we execute it
                if (mBuffer.getSize() > 0) {
                    // put on the screen the command 
                    update("COMMAND: " + mBuffer + "\n");
                    // call Lua 
                    LuaAPI::script(mBuffer);
                }

                // Reset to the default text
                mBuffer = mDefaultText;
            } else if (evt.text.unicode == 9) {
                // Here we handle the tab
                // first get the command name
                sf::String cmd = mBuffer;
                // remove the first char's to get the real command
                cmd.erase(0, 4);

                // and finally we compare if the buffer contains the cmd
                // if not we set the cmd_check to new command
                if (cmd_check == sf::String("") || mBuffer.find(cmd_check) == sf::String::InvalidPos) {
                    cmd_check = cmd;
                }
                
                // store the result hint
                sf::String result = sf::String(LuaFunctions::getTypeHint(cmd_check.toAnsiString()));

                // if we get an hint
                if (result.getSize() > 0) {
                    // an then we set the buffer
                    mBuffer = mDefaultText + result;
                }

            } else if (evt.text.unicode == 8) {
                if (mBuffer.getSize() > 4) {

                    // We remove the size - 1
                    // thats means the letter 
                    mBuffer.erase(mBuffer.getSize() - 1);
                    mBuffer = mBuffer;
                }
            } else {
                // just put the char to the buffer
                mBuffer = mBuffer + evt.text.unicode;
            }

            // set the string to the text
            mText->setString(mBuffer);
        }   
    }
}

void LuaConsole::update(const sf::String& buffer) {
    mBufferOutput = mBufferOutput + buffer;

   mOutput->setString(mBufferOutput);

   // if we dont have scrolled yet we will automatic update the ouput position
    if (mHasScrolled == false) {
        mOutput->setPosition(Vect2f(mBG->getPosition().x, mConsoleSize.y - mOutput->getSize().y - mLineHeight));
    }
}

void LuaConsole::registerEngine(MedievalEngine* engine) {
    mResources  = engine->getResourceManager();
    mWindowSize = engine->getWindow()->getSize();

    mConsoleSize.x = static_cast<int>(mWindowSize.x * 0.98f);
    mConsoleSize.y = static_cast<int>(mWindowSize.y * 0.98f);

    mMargin.x = mWindowSize.x * 0.01f;
    mMargin.y = mWindowSize.y * 0.01f;

    ResourceID textID;
    ResourceID outputID;
    ResourceID bgID;
    ResourceID lineEditID;
    ResourceID fontID;

    fontID = mResources->loadFont("system/Inconsolata.ttf");
    
    outputID = textID = mResources->createText(sf::String(""), Window::fontSize(0.20f), fontID);
    mOutput  = mResources->getResource<Text>(outputID);

    textID = mResources->createText(mBuffer, Window::fontSize(0.25f), fontID);
    mText  = mResources->getResource<Text>(textID);
    // MAGIC NUMBER WHERE! for some reason we have to multiply the text size
    // by 2 for get the right size of the height
    // TODO(pedro): why whis happens?
    mLineHeight = mText->getSize().y * 2; 
    mText->setString(mBuffer);
    mNumberLines = 1;

    bgID = mResources->createShape(mConsoleSize, mBGColor, mMargin);
    mBG  = mResources->getResource<Shape>(bgID);

    lineEditID = mResources->createShape(Vect2f(static_cast<float>(mConsoleSize.x),  mLineHeight), mBGColor);
    mLineEdit  = mResources->getResource<Shape>(lineEditID);

    mLineEdit->setPosition(Vect2f(mBG->getPosition().x, mBG->getPosition().y + mBG->getSize().y - mLineHeight));
    mText->setPosition(mLineEdit->getPosition());  

    // Get the messages from the log
    LOG_OBJECT->setObserver(this);
}

void LuaConsole::draw(Window& window) {
    if (mClockBlinkCursor.getMilliSeconds() > mCusorBlinkTime) {
        if (mCursor == "|") {
            mCursor = " ";
        } else {
            mCursor = "|";
        }
        mClockBlinkCursor.restart();
        mText->setString(mBuffer + mCursor);
    }


    if (mText != nullptr && mBG != nullptr && mLineEdit != nullptr && mOutput != nullptr) {
        window.draw(mBG);
        window.draw(mLineEdit);

        Area mBGArea   = mBG->getGlobalBounds();
        mBGArea.height = mBGArea.height - mLineHeight;

        sf::View panelView;
        sf::FloatRect panelRect(mBGArea.left / mWindowSize.x,
                                (mBGArea.top) / mWindowSize.y,
                                (mBGArea.width) / mWindowSize.x,
                                (mBGArea.height) / mWindowSize.y);

        panelView.reset(sf::FloatRect(mBGArea.left, mBGArea.top,
                                      mBGArea.width, mBGArea.height));

        panelView.setViewport(panelRect);
        window.getWindowPtr()->setView(panelView);

        window.draw(mOutput);

        window.getWindowPtr()->setView(window.getWindowPtr()->getDefaultView());

        window.draw(mText);
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
