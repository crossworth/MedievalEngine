#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H
#include <map>
#include <LogInc.h>
#include <Helper/ID.h>
#include <Helper/Data2.h>
#include <Helper/Types.h>
#include <Assets/Asset.h>
#include <Assets/Texture.h>
#include <Assets/Sprite.h>
#include <Assets/Font.h>
#include <Assets/Text.h>
#include <Assets/SpriteAnimation.h>
#include <Assets/Music.h>
#include <Assets/Sound.h>
#include <Assets/Shape.h>


namespace ME {

class AssetsManager {
public:
    static AssetsManager* getInstance();

    MEid loadTexture(const std::string& fileName);
    MEid loadFont(const std::string& fileName);
    MEid loadFont(SM::BYTE* bytes, std::size_t size);
    MEid loadMusic(const std::string& fileName);
    MEid loadSound(const std::string& fileName);

    MEid createSprite(const MEid& texture);
    MEid createText(const std::wstring& text, const unsigned int& fontSize, const MEid& font);
    MEid createSpriteAnimation();
    MEid createShape(const Vect2f& size = Vect2f(50.f, 50.0f), const Color& color = Color(Color::WHITE), const Vect2f& pos = Vect2f(0.0f, 0.0f));

    template<typename T>
    T* getAsset(const MEid& id);

    ~AssetsManager();
private:
    static AssetsManager* mInstance;
    std::map<MEid, Asset*> mAssets;

    AssetsManager();
};

template<typename T>
T* AssetsManager::getAsset(const MEid &id) {
    if (mAssets.find(id) != mAssets.end()) {
        return static_cast<T*>(mAssets[id]);
    } else {
        LOG << Log::WARNING << ("[AssetsManager::getAsset] Asset not found ID: " + Data2::int_to_str(id)).c_str() << std::endl;
        return static_cast<T*>(new Asset);
    }
}

}

#endif // ASSETSMANAGER_H
