#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H
#include <unordered_map>
#include <memory>
#include <LogInc.h>
#include <Helper/Data2.h>
#include <Helper/Types.h>
#include <Resources/ResourceIDGenerator.h>
#include <Resources/Texture.h>
#include <Resources/Sprite.h>
#include <Resources/Font.h>
#include <Resources/Text.h>
#include <Resources/SpriteAnimation.h>
#include <Resources/Music.h>
#include <Resources/Sound.h>
#include <Resources/Shape.h>


namespace ME {

class ResourceManager {
public:
    ResourceManager();

    ResourceID loadTexture(const std::string& fileName);
    ResourceID loadFont(const std::string& fileName);
    ResourceID loadFont(SM::BYTE* bytes, std::size_t size);
    ResourceID loadMusic(const std::string& fileName);
    ResourceID loadSound(const std::string& fileName);

    ResourceID createSprite(const ResourceID& texture);
    ResourceID createText(const std::wstring& text,
                    const unsigned int& fontSize,
                    const ResourceID& font);

    ResourceID createSpriteAnimation();
    ResourceID createShape(const Vect2f& size = Vect2f(50.f, 50.0f),
                     const Color& color = Color(Color::WHITE),
                     const Vect2f& pos = Vect2f(0.0f, 0.0f));

    template<typename T>
    T* getAsset(const ResourceID& id);

    ~ResourceManager();
private:
    typedef std::shared_ptr<Resource> ResourcePtr;
    std::unordered_map<ResourceID, ResourcePtr> mAssets;
};

template<typename T>
T* ResourceManager::getAsset(const ResourceID &id) {
    if (mAssets.find(id) != mAssets.end()) {
        return static_cast<T*>(mAssets[id].get());
    } else {
        LOG << Log::WARNING << ("[AssetsManager::getAsset] Asset not found ID: "
                                + Data2::int_to_str(id)).c_str() << std::endl;
        return nullptr;
    }
}

}

#endif // ASSETSMANAGER_H
