#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H
#include <unordered_map>
#include <LogInc.h>
#include <Assets/AssetIDGenerator.h>
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
    AssetsManager();

    AssetID loadTexture(const std::string& fileName);
    AssetID loadFont(const std::string& fileName);
    AssetID loadFont(SM::BYTE* bytes, std::size_t size);
    AssetID loadMusic(const std::string& fileName);
    AssetID loadSound(const std::string& fileName);

    AssetID createSprite(const AssetID& texture);
    AssetID createText(const std::wstring& text,
                    const unsigned int& fontSize,
                    const AssetID& font);

    AssetID createSpriteAnimation();
    AssetID createShape(const Vect2f& size = Vect2f(50.f, 50.0f),
                     const Color& color = Color(Color::WHITE),
                     const Vect2f& pos = Vect2f(0.0f, 0.0f));

    template<typename T>
    T* getAsset(const AssetID& id);

    ~AssetsManager();
private:
    std::unordered_map<AssetID, Asset*> mAssets;
};

template<typename T>
T* AssetsManager::getAsset(const AssetID &id) {
    if (mAssets.find(id) != mAssets.end()) {
        return static_cast<T*>(mAssets[id]);
    } else {
        LOG << Log::WARNING << ("[AssetsManager::getAsset] Asset not found ID: "
                                + Data2::int_to_str(id)).c_str() << std::endl;
        return nullptr;
    }
}

}

#endif // ASSETSMANAGER_H