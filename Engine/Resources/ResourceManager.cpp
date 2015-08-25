#include "ResourceManager.h"

using namespace ME;

ResourceManager::ResourceManager() {
    LOG << Log::VERBOSE
        << "[AssetsManager::AssetsManager] AssetsManager created" << std::endl;
}

ResourceID ResourceManager::loadTexture(const std::string &fileName) {
    ResourceID textureID = ResourceIDGenerator::get();
    mAssets[textureID]   = ResourcePtr(new Texture(fileName));

    LOG << Log::VERBOSE
        << ("[AssetsManager::loadTexture] Texture loaded ID: " +
            Data2::int_to_str(textureID)).c_str() << std::endl;

    return textureID;
}

ResourceID ResourceManager::loadFont(const std::string &fileName) {
    ResourceID fontID = ResourceIDGenerator::get();
    mAssets[fontID]   = ResourcePtr(new Font(fileName));

    LOG << Log::VERBOSE << ("[AssetsManager::loadFont] Font loaded ID: " +
                            Data2::int_to_str(fontID)).c_str() << std::endl;

    return fontID;
}

ResourceID ResourceManager::loadFont(SM::BYTE* bytes, std::size_t size) {
    ResourceID fontID = ResourceIDGenerator::get();
    mAssets[fontID]   = ResourcePtr(new Font());
    getResource<Font>(fontID)->loadFromMemory(bytes, size);

    LOG << Log::VERBOSE
        << ("[AssetsManager::loadFont] Font loaded from memory ID: " +
            Data2::int_to_str(fontID)).c_str() << std::endl;

    return fontID;
}

ResourceID ResourceManager::loadMusic(const std::string &fileName) {
    ResourceID musicID = ResourceIDGenerator::get();
    mAssets[musicID]   = ResourcePtr(new Music(fileName));

    LOG << Log::VERBOSE << ("[AssetsManager::loadMusic] Music loaded ID: " +
                            Data2::int_to_str(musicID)).c_str() << std::endl;

    return musicID;
}

ResourceID ResourceManager::loadSound(const std::string &fileName) {
    ResourceID soundID = ResourceIDGenerator::get();
    mAssets[soundID]   = ResourcePtr(new Sound(fileName));

    LOG << Log::VERBOSE << ("[AssetsManager::loadSound] Sound loaded ID: " +
                            Data2::int_to_str(soundID)).c_str() << std::endl;

    return soundID;
}

ResourceID ResourceManager::createSprite(const ResourceID &texture) {
    ResourceID spriteID = ResourceIDGenerator::get();
    mAssets[spriteID]   = ResourcePtr(new Sprite());
    getResource<Sprite>(spriteID)->setTexture(getResource<Texture>(texture));

    LOG << Log::VERBOSE
        << ("[AssetsManager::createSprite] Sprite created ID: " +
            Data2::int_to_str(spriteID)).c_str() << std::endl;

    return spriteID;
}

ResourceID ResourceManager::createSpriteAnimation() {
    ResourceID spriteAnID = ResourceIDGenerator::get();
    mAssets[spriteAnID]   = ResourcePtr(new SpriteAnimation());

    LOG << Log::VERBOSE
        << ("[AssetsManager::createSpriteAnimation] SpriteAnimation created ID: "
            + Data2::int_to_str(spriteAnID)).c_str() << std::endl;

    return spriteAnID;
}

ResourceID ResourceManager::createShape(const Vect2f &size,
                                const Color &color,
                                const Vect2f &pos) {

    ResourceID shapeID = ResourceIDGenerator::get();
    mAssets[shapeID]   = ResourcePtr(new Shape(size, color, pos));

    LOG << Log::VERBOSE << ("[AssetsManager::createShape] Shape created ID: " +
                            Data2::int_to_str(shapeID)).c_str() << std::endl;

    return shapeID;
}

ResourceID ResourceManager::createText(const std::wstring &text,
                               const unsigned int &fontSize,
                               const ResourceID &font) {

    ResourceID textID = ResourceIDGenerator::get();
    mAssets[textID]   = ResourcePtr(new Text());
    getResource<Text>(textID)->setFont(*getResource<Font>(font));
    getResource<Text>(textID)->setFontSize(fontSize);
    getResource<Text>(textID)->setString(text);

    LOG << Log::VERBOSE << ("[AssetsManager::createText] Text created ID: " +
                            Data2::int_to_str(textID)).c_str() << std::endl;

    return textID;
}

ResourceManager::~ResourceManager() {
    LOG << Log::VERBOSE
        << "[AssetsManager::~AssetsManage] Cleaning everything..."
        << std::endl;

    for (unsigned int i = 0; i < mAssets.size(); i++) {
        mAssets.at(i).reset();
    }
    mAssets.clear();
}
