#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H
#include <map>
#include <LogInc.h>
#include <Assets/Asset.h>
#include <Helper/ID.h>
#include <Helper/Data2.h>
#include <Assets/Texture.h>
#include <Assets/Sprite.h>
#include <Assets/Font.h>
#include <Assets/Text.h>
#include <Assets/SpriteAnimation.h>
#include <Assets/Music.h>
#include <Assets/Sound.h>


namespace ME {

class AssetsManager {
public:
    static AssetsManager* getInstance();

    MEid loadTexture(const std::string &fileName);
    MEid loadFont(const std::string &fileName);
    MEid loadMusic(const std::string &fileName);
    MEid loadSound(const std::string &fileName);

    MEid createSprite(const MEid &texture);
    MEid createText(const std::string &text, const unsigned int &fontSize, const MEid &font);
    MEid createSpriteAnimation();

    Asset* getAsset(const MEid &id);

private:
    static AssetsManager* mInstance;
    std::map<MEid, Asset*> mAssets;

    AssetsManager();
};

}

#endif // ASSETSMANAGER_H
