#include "mainstate.h"
#include "gameengine.h"

using namespace ME;

mainState::mainState(){

}


void mainState::init()
{
    mLua->doFile(globalPath+"scripts/mainState/init.lua");
}

void mainState::render(){
   mLua->doFile(globalPath+"scripts/mainState/render.lua");
}


void mainState::handleEvents(){
    while(mRender->pollEvent(mEvent)){
        if ( mEvent.type == sf::Event::Closed || ( mEvent.type == sf::Event::KeyPressed && mEvent.key.code == sf::Keyboard::Escape ) ){
            mLua->doFile(globalPath+"scripts/mainState/close.lua");
            mRender->close();
        }
        if ( mEvent.type == sf::Event::GainedFocus){
            mLua->doFile(globalPath+"scripts/mainState/gainedFocus.lua");
            mRender->hasFocus = true;
        }
        if ( mEvent.type == sf::Event::LostFocus){
            mRender->hasFocus = false;
            mLua->doFile(globalPath+"scripts/mainState/lostFocus.lua");
        }
        if ( mEvent.type == sf::Event::KeyReleased){
            mLua->doFile(globalPath+"scripts/mainState/keyReleased.lua");
        }
        if ( mEvent.type == sf::Event::KeyPressed){
            if ( mEvent.key.code == sf::Keyboard::L){

            }
            if ( mEvent.key.code == sf::Keyboard::C){

            }

            mLua->doFile(globalPath+"scripts/mainState/keyPressed.lua");
        }
        if ( mEvent.type == sf::Event::MouseButtonPressed){
            mLua->doFile(globalPath+"scripts/mainState/mouseButtonPressed.lua");
        }
        if ( mEvent.type == sf::Event::MouseButtonReleased){
            mLua->doFile(globalPath+"scripts/mainState/mouseButtonReleased.lua");
        }
        if ( mEvent.type == sf::Event::MouseWheelMoved){
            mLua->doFile(globalPath+"scripts/mainState/mouseWheelEvent.lua");
        }
    }
}

mainState::~mainState(){

}

void mainState::update(){
    mLua->doFile(globalPath+"scripts/mainState/update.lua");
}


void mainState::restart(){
    this->init();
}

void mainState::play(){
    running = true;
}

void mainState::pause(){
    running = false;
}
