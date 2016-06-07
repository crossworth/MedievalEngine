#include "ResourceManager.h"

using namespace ME;

std::unordered_map<ResourceID, ResourcePtr> ResourceManager::mResources;

void ResourceManager::updateAudioVolume() {
    for(unsigned long i = 0; i < ResourceManager::mResources.size(); i++) {
        if (ResourceManager::mResources.at(i)->getType() == Resource::Type::MUSIC) {
            ResourcePtr resource = ResourceManager::mResources.at(i);

            Music *music = reinterpret_cast<Music*>(resource.get());
            music->updateVolume();
        }

        if (ResourceManager::mResources.at(i)->getType() == Resource::Type::SOUND) {
            ResourcePtr resource = ResourceManager::mResources.at(i);

            Sound *sound = reinterpret_cast<Sound*>(resource.get());
            sound->updateVolume();
        }
    }
}

ResourceManager::ResourceManager() {
    LOG << Log::VERBOSE
        << "[AssetsManager::AssetsManager] AssetsManager created" << std::endl;
}

ResourceID ResourceManager::loadTexture(const std::string& fileName) {
    ResourceID textureID  = ResourceIDGenerator::get();
    ResourceManager::mResources[textureID] = ResourcePtr(new Texture(fileName));

    LOG << Log::VERBOSE
        << "[AssetsManager::loadTexture] Texture loaded ID: "
        << Kit::int_str(textureID) << std::endl;

    return textureID;
}

ResourceID ResourceManager::loadFont(const std::string& fileName) {
    ResourceID fontID  = ResourceIDGenerator::get();
    ResourceManager::mResources[fontID] = ResourcePtr(new Font());
    getResource<Font>(fontID)->loadFromFile(fileName);

    LOG << Log::VERBOSE
        << "[AssetsManager::loadFont] Font loaded ID: "
        << Kit::int_str(fontID) << std::endl;

    return fontID;
}

ResourceID ResourceManager::loadFont(MEByte* bytes, std::size_t size) {
    ResourceID fontID  = ResourceIDGenerator::get();
    ResourceManager::mResources[fontID] = ResourcePtr(new Font());
    getResource<Font>(fontID)->loadFromMemory(bytes, size);

    LOG << Log::VERBOSE
        << "[AssetsManager::loadFont] Font loaded from memory ID: "
        << Kit::int_str(fontID) << std::endl;

    return fontID;
}

ResourceID ResourceManager::loadMusic(const std::string& fileName) {
    ResourceID musicID  = ResourceIDGenerator::get();
    ResourceManager::mResources[musicID] = ResourcePtr(new Music());
    getResource<Music>(musicID)->loadFromFile(fileName);

    LOG << Log::VERBOSE
        << "[AssetsManager::loadMusic] Music loaded ID: "
        << Kit::int_str(musicID) << std::endl;

    return musicID;
}

ResourceID ResourceManager::loadSound(const std::string& fileName) {
    ResourceID soundID  = ResourceIDGenerator::get();
    ResourceManager::mResources[soundID] = ResourcePtr(new Sound(fileName));

    LOG << Log::VERBOSE
        << "[AssetsManager::loadSound] Sound loaded ID: "
        << Kit::int_str(soundID) << std::endl;

    return soundID;
}

ResourceID ResourceManager::createSprite(const ResourceID& texture) {
    ResourceID spriteID  = ResourceIDGenerator::get();
    ResourceManager::mResources[spriteID] = ResourcePtr(new Sprite());
    getResource<Sprite>(spriteID)->setTexture(getResource<Texture>(texture));

    LOG << Log::VERBOSE
        << "[AssetsManager::createSprite] Sprite created ID: "
        << Kit::int_str(spriteID) << std::endl;

    return spriteID;
}

ResourceID ResourceManager::createSpriteAnimation() {
    ResourceID spriteAnID  = ResourceIDGenerator::get();
    ResourceManager::mResources[spriteAnID] = ResourcePtr(new SpriteAnimation());

    LOG << Log::VERBOSE
        << "[AssetsManager::createSpriteAnimation] SpriteAnimation created ID: "
        << Kit::int_str(spriteAnID) << std::endl;

    return spriteAnID;
}

ResourceID ResourceManager::createShape(const Vect2f& size,
                                const Color& color,
                                const Vect2f& pos) {

    ResourceID shapeID  = ResourceIDGenerator::get();
    ResourceManager::mResources[shapeID] = ResourcePtr(new Shape(size, color, pos));

    LOG << Log::VERBOSE
        << "[AssetsManager::createShape] Shape created ID: "
        << Kit::int_str(shapeID) << std::endl;

    return shapeID;
}

ResourceID ResourceManager::createText(const String& text,
                               const unsigned int& fontSize,
                               const ResourceID& font) {

    ResourceID textID  = ResourceIDGenerator::get();
    ResourceManager::mResources[textID] = ResourcePtr(new Text());
    getResource<Text>(textID)->setFont(*getResource<Font>(font));
    getResource<Text>(textID)->setFontSize(fontSize);
    getResource<Text>(textID)->setString(text);

    LOG << Log::VERBOSE
        << "[AssetsManager::createText] Text created ID: "
        << Kit::int_str(textID) << std::endl;

    return textID;
}

ResourceManager::~ResourceManager() {
    LOG << Log::VERBOSE
        << "[AssetsManager::~AssetsManage] Cleaning everything..."
        << std::endl;

    for (unsigned int i = 0; i < ResourceManager::mResources.size(); i++) {
        ResourceManager::mResources.at(i).reset();
    }

    ResourceManager::mResources.clear();
}
