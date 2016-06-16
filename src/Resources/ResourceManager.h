#ifndef MEDIEVALENGINE_RESOURCES_RESOURCEMANAGER_H_
#define MEDIEVALENGINE_RESOURCES_RESOURCEMANAGER_H_
#include <memory>
#include <unordered_map>

#include "Helper/Kit.h"

#include "Lua/LuaAPI.h"

#include "Resources/Text.h"
#include "Resources/Sound.h"
#include "Resources/Shape.h"
#include "Resources/Script.h"
#include "Resources/Sprite.h"
#include "Resources/MusicQueue.h"
#include "Resources/SpriteAnimation.h"

namespace ME {

typedef std::shared_ptr<Resource> ResourcePtr;

class ResourceManager {
public:
    static void registerLuaFunctions();

    static void clear();

    static void updateAudibleVolume();

    static bool loadTexture(const std::string &resourceName);

    static bool loadFont(const std::string &resourceName);
    static bool loadFont(const std::string &resourceName, byte *bytes, const uint64 &size);

    static bool loadMusic(const std::string &resourceName);

    static bool loadSound(const std::string &resourceName);

    static bool createSprite(const std::string &resourceName, const std::string &texture);

    static bool createText(const std::string &resourceName, const String &text,
                    const unsigned int &fontSize,
                    const std::string &font = Font::Default);

    static bool createSpriteAnimation(const std::string &resourceName);
    static bool createShape(const std::string &resourceName, const Vect2f &size = Vect2f(50.f, 50.0f),
                     const Color &color = Color(Color::WHITE),
                     const Vect2f &pos = Vect2f(0.0f, 0.0f));

    template<typename T>
    static T* get(const std::string &name);

    static bool inline exists(const std::string &name) {
        return (ResourceManager::mResources.find(name) != ResourceManager::mResources.end());
    }

protected:
    // NOTE(Pedro): We can use an std::map if we need more memory, but the speed will pay for this change
    static std::unordered_map<std::string, ResourcePtr> mResources;
private:
    ResourceManager();
};

template<typename T>
T* ResourceManager::get(const std::string &name) {
    // TODO(pedro): veriify if it's valid resource before delivery to the user
    // if it's not valid we return a fallback
    // resource or something

    T* resourcePtr = nullptr;

    if (ResourceManager::mResources.find(name) != ResourceManager::mResources.end()) {
        resourcePtr =  static_cast<T*>(ResourceManager::mResources[name].get());
    }

    if (resourcePtr == nullptr || resourcePtr->isValid() == false) {
        LOG << Log::WARNING
            << "[ResourceManager::get] Resource not found or is invalid: "
            << name << std::endl;
    }

    // TODO(Pedro): load an Default Error or invalid resource
    // and return it here

    return resourcePtr;
}

}

#endif // MEDIEVALENGINE_RESOURCES_RESOURCEMANAGER_H_
