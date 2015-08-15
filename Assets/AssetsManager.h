#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H
#include <map>
#include <LogInc.h>
#include <Assets/Asset.h>
#include <Helper/ID.h>
#include <Assets/Texture.h>
#include <Assets/Sprite.h>


namespace ME {

class AssetsManager {
public:
    static AssetsManager* getInstance();
    ~AssetsManager();

    MEid loadTexture(const std::string &fileName);
    MEid createSprite(const MEid &texture);

    Asset* getAsset(const MEid &id);

private:
    static AssetsManager* mInstance;
    std::map<MEid, Asset*> mAssets;

    AssetsManager();
};

}

#endif // ASSETSMANAGER_H
