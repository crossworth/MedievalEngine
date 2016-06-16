#include "ResourceManager.h"

using namespace ME;

std::unordered_map<std::string, ResourcePtr> ResourceManager::mResources;

void ResourceManager::updateAudibleVolume() {
    std::unordered_map<std::string, ResourcePtr>::iterator index;
    index = ResourceManager::mResources.begin();

    for(; index != ResourceManager::mResources.end(); index++) {
        if (index->second->getType() == Resource::Type::MUSIC) {
            ResourcePtr resource = index->second;

            Music *music = reinterpret_cast<Music*>(resource.get());
            music->updateVolume();
        }

        if (index->second->getType() == Resource::Type::SOUND) {
            ResourcePtr resource = index->second;

            Sound *sound = reinterpret_cast<Sound*>(resource.get());
            sound->updateVolume();
        }
    }
}

ResourceManager::ResourceManager() {
    // We dont have a constructor
}

void ResourceManager::registerLuaFunctions() {
    LuaAPI::state.set_function("load_texture", &ResourceManager::loadTexture);
    LuaExportAPI::exports("load_texture", "string", "bool", LuaExportType::FUNCTION, "Load a texture file");
}

bool ResourceManager::loadTexture(const std::string &resourceName) {
    if (ResourceManager::exists(resourceName) && ResourceManager::mResources[resourceName].get()->isValid()) {
        return true;
    }

    ResourceManager::mResources[resourceName] = ResourcePtr(new Texture(resourceName));

    if (ResourceManager::mResources[resourceName].get()->isValid()) {
        LOG << Log::VERBOSE
            << "[ResourceManager::loadTexture] Texture loaded: "
            << resourceName << std::endl;
        return true;
    } else {
        return false;
    }
}

bool ResourceManager::loadFont(const std::string &resourceName) {
    if (ResourceManager::exists(resourceName) && ResourceManager::mResources[resourceName].get()->isValid()) {
        return true;
    }

    ResourceManager::mResources[resourceName] = ResourcePtr(new Font());
    static_cast<Font*>(ResourceManager::mResources[resourceName].get())->loadFromFile(resourceName);

    if (ResourceManager::mResources[resourceName].get()->isValid()) {
        LOG << Log::VERBOSE
            << "[ResourceManager::loadFont] Font loaded: "
            << resourceName << std::endl;
        return true;
    } else {
        return false;
    }
}

bool ResourceManager::loadFont(const std::string &resourceName, byte *bytes, const uint64 &size) {
    if (ResourceManager::exists(resourceName) && ResourceManager::mResources[resourceName].get()->isValid()) {
        return true;
    }

    ResourceManager::mResources[resourceName] = ResourcePtr(new Font());
    static_cast<Font*>(ResourceManager::mResources[resourceName].get())->loadFromMemory(bytes, size);

    if (ResourceManager::mResources[resourceName].get()->isValid()) {
        LOG << Log::VERBOSE
            << "[ResourceManager::loadFont] Font loaded from Memory: "
            << resourceName << std::endl;
        return true;
    } else {
        return false;
    }
}

bool ResourceManager::loadMusic(const std::string &resourceName) {
    if (ResourceManager::exists(resourceName) && ResourceManager::mResources[resourceName].get()->isValid()) {
        return true;
    }

    ResourceManager::mResources[resourceName] = ResourcePtr(new Music());
    static_cast<Music*>(ResourceManager::mResources[resourceName].get())->loadFromFile(resourceName);

    if (ResourceManager::mResources[resourceName].get()->isValid()) {
        LOG << Log::VERBOSE
            << "[ResourceManager::loadMusic] Music loaded: "
            << resourceName << std::endl;
        return true;
    } else {
        return false;
    }
}

bool ResourceManager::loadSound(const std::string &resourceName) {
    if (ResourceManager::exists(resourceName) && ResourceManager::mResources[resourceName].get()->isValid()) {
        return true;
    }

    ResourceManager::mResources[resourceName] = ResourcePtr(new Sound(resourceName));

    if (ResourceManager::mResources[resourceName].get()->isValid()) {
        LOG << Log::VERBOSE
            << "[ResourceManager::loadSound] Sound loaded: "
            << resourceName << std::endl;
        return true;
    } else {
        return false;
    }
}

bool ResourceManager::createSprite(const std::string &resourceName, const std::string &texture) {
    if (ResourceManager::exists(resourceName) && ResourceManager::mResources[resourceName].get()->isValid()) {
        return true;
    }

    ResourceManager::mResources[resourceName] = ResourcePtr(new Sprite());
    static_cast<Sprite*>(ResourceManager::mResources[resourceName].get())->setTexture(ResourceManager::get<Texture>(texture));

    if (ResourceManager::mResources[resourceName].get()->isValid()) {
        LOG << Log::VERBOSE
            << "[ResourceManager::createSprite] Sprite created: "
            << resourceName << std::endl;
        return true;
    } else {
        return false;
    }
}

bool ResourceManager::createSpriteAnimation(const std::string &resourceName) {
    if (ResourceManager::exists(resourceName) && ResourceManager::mResources[resourceName].get()->isValid()) {
        return true;
    }

    ResourceManager::mResources[resourceName] = ResourcePtr(new SpriteAnimation());

    if (ResourceManager::mResources[resourceName].get()->isValid()) {
        LOG << Log::VERBOSE
            << "[ResourceManager::createSpriteAnimation] SpriteAnimation created: "
            << resourceName << std::endl;
        return true;
    } else {
        return false;
    }
}

bool ResourceManager::createShape(const std::string &resourceName, const Vect2f &size,
                                const Color &color,
                                const Vect2f &pos) {

    ResourceManager::mResources[resourceName] = ResourcePtr(new Shape(size, color, pos));

    if (ResourceManager::mResources[resourceName].get()->isValid()) {
        LOG << Log::VERBOSE
            << "[ResourceManager::createShape] Shape created: "
            << resourceName << std::endl;
        return true;
    } else {
        return false;
    }
}

bool ResourceManager::createText(const std::string &resourceName, const String &text,
                               const unsigned int &fontSize,
                               const std::string &font) {

    if (ResourceManager::exists(resourceName) && ResourceManager::mResources[resourceName].get()->isValid()) {
        return true;
    }

    ResourceManager::mResources[resourceName] = ResourcePtr(new Text());
    static_cast<Text*>(ResourceManager::mResources[resourceName].get())->setFont(*ResourceManager::get<Font>(font));
    static_cast<Text*>(ResourceManager::mResources[resourceName].get())->setFontSize(fontSize);
    static_cast<Text*>(ResourceManager::mResources[resourceName].get())->setString(text);

    if (ResourceManager::mResources[resourceName].get()->isValid()) {
        LOG << Log::VERBOSE
            << "[ResourceManager::createText] Text created: "
            << resourceName << std::endl;
        return true;
    } else {
        return false;
    }
}

void ResourceManager::clear() {
    LOG << Log::VERBOSE
        << "[ResourceManager::clear] Cleaning everything..."
        << std::endl;

    std::unordered_map<std::string, ResourcePtr>::iterator index;
    index = ResourceManager::mResources.begin();

    for(; index != ResourceManager::mResources.end(); index++) {
        index->second.reset();
    }

    ResourceManager::mResources.clear();
}
