#include "ResourceManager.h"

using namespace ME;

ResourceManager::ResourceManager() {
    LOG << Log::VERBOSE
        << "[AssetsManager::AssetsManager] AssetsManager created" << std::endl;
}

ResourceID ResourceManager::loadTexture(const std::string& fileName) {
    ResourceID textureID   = ResourceIDGenerator::get();
    mResources[textureID] = ResourcePtr(new Texture(fileName));

    LOG << Log::VERBOSE
        << ("[AssetsManager::loadTexture] Texture loaded ID: " +
            Kit::int_str(textureID)).c_str() << std::endl;

    return textureID;
}

ResourceID ResourceManager::loadFont(const std::string& fileName) {
    ResourceID fontID   = ResourceIDGenerator::get();
    mResources[fontID] = ResourcePtr(new Font(fileName));

    LOG << Log::VERBOSE << ("[AssetsManager::loadFont] Font loaded ID: " +
                            Kit::int_str(fontID)).c_str() << std::endl;

    return fontID;
}

ResourceID ResourceManager::loadFont(MEByte* bytes, std::size_t size) {
    ResourceID fontID   = ResourceIDGenerator::get();
    mResources[fontID] = ResourcePtr(new Font());
    getResource<Font>(fontID)->loadFromMemory(bytes, size);

    LOG << Log::VERBOSE
        << ("[AssetsManager::loadFont] Font loaded from memory ID: " +
            Kit::int_str(fontID)).c_str() << std::endl;

    return fontID;
}

ResourceID ResourceManager::loadMusic(const std::string& fileName) {
    ResourceID musicID   = ResourceIDGenerator::get();
    mResources[musicID] = ResourcePtr(new Music(fileName));

    LOG << Log::VERBOSE << ("[AssetsManager::loadMusic] Music loaded ID: " +
                            Kit::int_str(musicID)).c_str() << std::endl;

    return musicID;
}

ResourceID ResourceManager::loadSound(const std::string& fileName) {
    ResourceID soundID   = ResourceIDGenerator::get();
    mResources[soundID] = ResourcePtr(new Sound(fileName));

    LOG << Log::VERBOSE << ("[AssetsManager::loadSound] Sound loaded ID: " +
                            Kit::int_str(soundID)).c_str() << std::endl;

    return soundID;
}

ResourceID ResourceManager::createSprite(const ResourceID& texture) {
    ResourceID spriteID   = ResourceIDGenerator::get();
    mResources[spriteID] = ResourcePtr(new Sprite());
    getResource<Sprite>(spriteID)->setTexture(getResource<Texture>(texture));

    LOG << Log::VERBOSE
        << ("[AssetsManager::createSprite] Sprite created ID: " +
            Kit::int_str(spriteID)).c_str() << std::endl;

    return spriteID;
}

ResourceID ResourceManager::createSpriteAnimation() {
    ResourceID spriteAnID   = ResourceIDGenerator::get();
    mResources[spriteAnID] = ResourcePtr(new SpriteAnimation());

    LOG << Log::VERBOSE
        << ("[AssetsManager::createSpriteAnimation] SpriteAnimation created ID: "
            + Kit::int_str(spriteAnID)).c_str() << std::endl;

    return spriteAnID;
}

ResourceID ResourceManager::createShape(const Vect2f& size,
                                const Color& color,
                                const Vect2f& pos) {

    ResourceID shapeID   = ResourceIDGenerator::get();
    mResources[shapeID] = ResourcePtr(new Shape(size, color, pos));

    LOG << Log::VERBOSE << ("[AssetsManager::createShape] Shape created ID: " +
                            Kit::int_str(shapeID)).c_str() << std::endl;

    return shapeID;
}

ResourceID ResourceManager::createText(const sf::String& text,
                               const unsigned int& fontSize,
                               const ResourceID& font) {

    ResourceID textID   = ResourceIDGenerator::get();
    mResources[textID] = ResourcePtr(new Text());
    getResource<Text>(textID)->setFont(*getResource<Font>(font));
    getResource<Text>(textID)->setFontSize(fontSize);
    getResource<Text>(textID)->setString(text);

    LOG << Log::VERBOSE << ("[AssetsManager::createText] Text created ID: " +
                            Kit::int_str(textID)).c_str() << std::endl;

    return textID;
}

ResourceManager::~ResourceManager() {
    LOG << Log::VERBOSE
        << "[AssetsManager::~AssetsManage] Cleaning everything..."
        << std::endl;

    for (unsigned int i = 0; i < mResources.size(); i++) {
        mResources.at(i).reset();
    }
    mResources.clear();
}