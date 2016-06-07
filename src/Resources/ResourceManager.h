#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <unordered_map>
#include "Helper/Kit.h"
#include "Resources/Sprite.h"
#include "Resources/Text.h"
#include "Resources/SpriteAnimation.h"
#include "Resources/MusicQueue.h"
#include "Resources/Sound.h"
#include "Resources/Shape.h"


namespace ME {

class ResourceManager {
public:
    ResourceManager();

    static void updateAudioVolume();

    ResourceID loadTexture(const std::string& fileName);
    ResourceID loadFont(const std::string& fileName);
    ResourceID loadFont(MEByte* bytes, std::size_t size);
    ResourceID loadMusic(const std::string& fileName);
    ResourceID loadSound(const std::string& fileName);

    ResourceID createSprite(const ResourceID& texture);
    ResourceID createText(const String& text,
                    const unsigned int& fontSize,
                    const ResourceID& font);

    ResourceID createSpriteAnimation();
    ResourceID createShape(const Vect2f& size = Vect2f(50.f, 50.0f),
                     const Color& color = Color(Color::WHITE),
                     const Vect2f& pos = Vect2f(0.0f, 0.0f));

    template<typename T>
    T* getResource(const ResourceID& id);

    ~ResourceManager();
protected:
    static std::unordered_map<ResourceID, ResourcePtr> mResources;
};

template<typename T>
T* ResourceManager::getResource(const ResourceID &id) {
    // TODO(pedro): veriify if it's valid resource before delivery to the user
    // if it's not valid we return a fallback
    // resource or something
    if (ResourceManager::mResources.find(id) != ResourceManager::mResources.end()) {
        return static_cast<T*>(ResourceManager::mResources[id].get());
    } else {
        LOG << Log::WARNING
            << "[AssetsManager::getAsset] Asset not found ID: "
            << Kit::int_str(id) << std::endl;

        return nullptr;
    }
}

}

#endif // RESOURCEMANAGER_H
