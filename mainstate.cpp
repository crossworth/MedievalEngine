#include "mainstate.h"
#include "gameengine.h"

using namespace ME;

mainState::mainState(){
}


void mainState::init()
{
    mLua->doFile("scripts/mainState/init.lua");

}

void mainState::render(){
   mRender->clear();
   mLua->doFile("scripts/mainState/render.lua");
   mRender->display();
}


void mainState::handleEvents(){
    while(mRender->pollEvent(mEvent)){
        if ( mEvent.type == sf::Event::Closed || ( mEvent.type == sf::Event::KeyPressed && mEvent.key.code == sf::Keyboard::Escape ) ){
            mLua->doFile("scripts/mainState/close.lua");
            mRender->close();
        }
        if ( mEvent.type == sf::Event::GainedFocus){
            mLua->doFile("scripts/mainState/gainedFocus.lua");
        }
        if ( mEvent.type == sf::Event::LostFocus){
            mLua->doFile("scripts/mainState/lostFocus.lua");
        }
        if ( mEvent.type == sf::Event::KeyReleased){
            mLua->doFile("scripts/mainState/keyReleased.lua");
        }
        if ( mEvent.type == sf::Event::KeyPressed){

            mLua->doFile("scripts/mainState/keyPressed.lua");
        }
        if ( mEvent.type == sf::Event::MouseButtonPressed){
            mLua->doFile("scripts/mainState/mouseButtonPressed.lua");
        }
        if ( mEvent.type == sf::Event::MouseButtonReleased){
            mLua->doFile("scripts/mainState/mouseButtonReleased.lua");
        }
        if ( mEvent.type == sf::Event::MouseWheelMoved){
            mLua->doFile("scripts/mainState/mouseWheelEvent.lua");
        }
    }
}

mainState::~mainState(){

}

void mainState::update(){
    mLua->doFile("scripts/mainState/update.lua");

}


void mainState::play(){
    running = true;
}

void mainState::pause(){
    running = false;
}
