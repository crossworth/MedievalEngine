#include "mainstate.h"
#include "gameengine.h"

using namespace ME;

mainState::mainState(){
    mEditor = editor::getInstance();
    open = false;
}


void mainState::init()
{
    mLua->doFile("scripts/mainState/init.lua");
    Sprite tmp;
    tmp.setTexture(*assets->loadAssetTexture("tile","assets/tile.png"));
    assets->loadAssetSprite("tile",tmp);
}

void mainState::render(){
   mRender->clear();
   mLua->doFile("scripts/mainState/render.lua");
   for(int i =0;i<tiles.size();i++){
       assets->getAssetSprite("tile")->setPosition(tiles.at(i).x,tiles.at(i).y);
        mRender->draw(*assets->getAssetSprite("tile"));
   }
   sf::Vector2i pos = sf::Mouse::getPosition(*mRender->getRenderWindow());
   assets->getAssetSprite("tile")->setPosition(pos.x,pos.y);
   mRender->draw(*assets->getAssetSprite("tile"));

   if ( open ){
       for(int i=0;i<mMap->numberTile;i++){
           assets->getAssetSprite(mMap->tiles[i].textureName)->setPosition(mMap->tiles[i].pos.x,mMap->tiles[i].pos.y);
           mRender->draw(*assets->getAssetSprite(mMap->tiles[i].textureName));
       }

   }

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
            if ( mEvent.key.code == sf::Keyboard::L){
                //this->restart();
                mMap = mEditor->open("assets/teste.map");

                //std::cout << "  " << mMap->numberTile ;
                //std::cout << "Number of tiles" << std::endl;


                for(int i=0;i< mMap->numberTile;i++){
                    assets->loadAssetTexture(mMap->tiles[i].textureName,mMap->tiles[i].textureName);
                     //std::cout << mMap->tiles[i].textureName << " Texture name "<< std::endl;
                    Sprite tmp;
                    tmp.setTexture(*assets->getAssetTexture(mMap->tiles[i].textureName));
                    assets->loadAssetSprite(mMap->tiles[i].textureName,tmp);

                }
                open =true;
            }
            if ( mEvent.key.code == sf::Keyboard::C){

                 mEditor->create("assets/teste.map");
            }

            mLua->doFile("scripts/mainState/keyPressed.lua");
        }
        if ( mEvent.type == sf::Event::MouseButtonPressed){
            Tile t;
            sf::Vector2i pos = sf::Mouse::getPosition(*mRender->getRenderWindow());
            t.pos.x = pos.x;
            t.pos.y = pos.y;
            Coord tmp;
            tmp.x = pos.x;
            tmp.y = pos.y;
            tiles.push_back(tmp);
            t.size.width = assets->getAssetSprite("tile")->getTexture()->getSize().x;
            t.size.height = assets->getAssetSprite("tile")->getTexture()->getSize().y;
            mEditor->insertTile(t);
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


void mainState::restart(){
    this->init();
}

void mainState::play(){
    running = true;
}

void mainState::pause(){
    running = false;
}
