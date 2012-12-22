#include "gui.h"

using namespace ME;

GUI::GUI()
{


}

GUI* GUI::getInstace(){
    static GUI* mGUI = new GUI();
    return mGUI;
}



std::string GUI::messageBox(const std::string &title,const std::string &message){
    AssetsManager* mAssets = AssetsManager::getInstance();
    renderWindow* mRender = renderWindow::getInstance();

    Sprite tmp;
    tmp.setTexture(*mAssets->loadAssetTexture("boxAsk",globalPath+"assets/ui/box.png"));
    tmp.setOrigin(tmp.getGlobalBounds().width/2,tmp.getGlobalBounds().height/2);
    tmp.setPosition(mRender->getWindowInformation().width/2,mRender->getWindowInformation().height/2);
    mAssets->loadAssetSprite("boxAsk",tmp);


    Text OKText;
    OKText.setString("OK");
    OKText.setFont(*mAssets->loadAssetFont("static",globalPath+"assets/fonts/static.ttf"));
    OKText.setCharacterSize(25);
    OKText.setPosition(tmp.getPosition().x+110,tmp.getPosition().y+45);


    Text ContText;
    ContText.setString(mMessagesBox[title]);
    ContText.setFont(*mAssets->getAssetFont("static"));
    ContText.setCharacterSize(25);
    ContText.setPosition(tmp.getPosition().x-175,tmp.getPosition().y);






    mRender->setCamera((sf::View)*mRender->getCamera("fixed"));

    mRender->draw(*mAssets->getAssetSprite("boxAsk"));


     sf::Vector2i mousePos = sf::Mouse::getPosition(*mRender->getRenderWindow());

     if (  OKText.getGlobalBounds().contains(mousePos.x,mousePos.y)){
         OKText.setColor(sf::Color(255,255,0));
         if ( sf::Mouse::isButtonPressed(sf::Mouse::Left)){
             if ( mMessagesBox[title].size() > 0)
                 return mMessagesBox[title];
             else
                 return "OK";
         }
     }

     mRender->draw(OKText);
     mRender->draw(ContText);

     sf::Event evt;

     while(mRender->getRenderWindow()->pollEvent(evt)){

         if ( evt.type = sf::Event::TextEntered){
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "A";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::B) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "B";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::C) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "C";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "D";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::E) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "E";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::F) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "F";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::G) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "G";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::H) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "H";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::I) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "I";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::J) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "J";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::K) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "K";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::L) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "L";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::M) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "M";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::N) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "N";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::O) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "O";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::P) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "P";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "Q";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::R) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "R";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "S";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::T) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "T";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::U) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "U";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::V) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "V";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "W";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::X) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "X";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "Y";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && mMessagesBox[title].size() <= 26) mMessagesBox[title] += "Z";
             if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::Delete) || sf::Keyboard::isKeyPressed(sf::Keyboard::Back)   && mMessagesBox[title].size() > 0) mMessagesBox[title] = mMessagesBox[title].substr(0,mMessagesBox[title].size()-1);
        }
    }


    return  "";
}
