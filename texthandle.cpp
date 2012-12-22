#include "texthandle.h"

using namespace ME;

TextHandle::TextHandle()
{
}




void TextHandle::TextShadow(const std::string &fileName,sf::RenderWindow &mWindow,const sf::Color &colorShadow,const sf::Vector2f &pos){
    AssetsManager* mAssets = AssetsManager::getInstance();
    sf::Color originalColor(mAssets->getAssetText(fileName)->getColor().r,mAssets->getAssetText(fileName)->getColor().g,mAssets->getAssetText(fileName)->getColor().b,mAssets->getAssetText(fileName)->getColor().a);
    sf::Vector2f originalPos(mAssets->getAssetText(fileName)->getPosition().x,mAssets->getAssetText(fileName)->getPosition().y);

    mAssets->getAssetText(fileName)->setColor(colorShadow);
    mAssets->getAssetText(fileName)->setPosition(mAssets->getAssetText(fileName)->getPosition().x+pos.x,mAssets->getAssetText(fileName)->getPosition().y+pos.y);
    mWindow.draw(*mAssets->getAssetText(fileName));

    mAssets->getAssetText(fileName)->setColor(originalColor);
    mAssets->getAssetText(fileName)->setPosition(originalPos);
    mWindow.draw(*mAssets->getAssetText(fileName));

    mAssets = nullptr;
    return;
}


