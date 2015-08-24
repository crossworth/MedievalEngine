#include "AssetsManager.h"

using namespace ME;

AssetsManager::AssetsManager() {
    LOG << Log::VERBOSE
        << "[AssetsManager::AssetsManager] AssetsManager created" << std::endl;
}

AssetID AssetsManager::loadTexture(const std::string &fileName) {
    AssetID textureID     = AssetIDGenerator::get();
    mAssets[textureID] = new Texture(fileName);

    LOG << Log::VERBOSE
        << ("[AssetsManager::loadTexture] Texture loaded ID: " +
            Data2::int_to_str(textureID)).c_str() << std::endl;

    return textureID;
}

AssetID AssetsManager::loadFont(const std::string &fileName) {
    AssetID fontID     = AssetIDGenerator::get();
    mAssets[fontID] = new Font(fileName);

    LOG << Log::VERBOSE << ("[AssetsManager::loadFont] Font loaded ID: " +
                            Data2::int_to_str(fontID)).c_str() << std::endl;

    return fontID;
}

AssetID AssetsManager::loadFont(SM::BYTE* bytes, std::size_t size) {
    AssetID fontID     = AssetIDGenerator::get();
    mAssets[fontID] = new Font();
    getAsset<Font>(fontID)->loadFromMemory(bytes, size);

    LOG << Log::VERBOSE
        << ("[AssetsManager::loadFont] Font loaded from memory ID: " +
            Data2::int_to_str(fontID)).c_str() << std::endl;

    return fontID;
}

AssetID AssetsManager::loadMusic(const std::string &fileName) {
    AssetID musicID     = AssetIDGenerator::get();
    mAssets[musicID] = new Music(fileName);

    LOG << Log::VERBOSE << ("[AssetsManager::loadMusic] Music loaded ID: " +
                            Data2::int_to_str(musicID)).c_str() << std::endl;

    return musicID;
}

AssetID AssetsManager::loadSound(const std::string &fileName) {
    AssetID soundID     = AssetIDGenerator::get();
    mAssets[soundID] = new Sound(fileName);

    LOG << Log::VERBOSE << ("[AssetsManager::loadSound] Sound loaded ID: " +
                            Data2::int_to_str(soundID)).c_str() << std::endl;

    return soundID;
}

AssetID AssetsManager::createSprite(const AssetID &texture) {
    AssetID spriteID     = AssetIDGenerator::get();
    mAssets[spriteID] = new Sprite();
    getAsset<Sprite>(spriteID)->setTexture(getAsset<Texture>(texture));

    LOG << Log::VERBOSE
        << ("[AssetsManager::createSprite] Sprite created ID: " +
            Data2::int_to_str(spriteID)).c_str() << std::endl;

    return spriteID;
}

AssetID AssetsManager::createSpriteAnimation() {
    AssetID spriteAnID     = AssetIDGenerator::get();
    mAssets[spriteAnID] = new SpriteAnimation();

    LOG << Log::VERBOSE
        << ("[AssetsManager::createSpriteAnimation] SpriteAnimation created ID: "
            + Data2::int_to_str(spriteAnID)).c_str() << std::endl;

    return spriteAnID;
}

AssetID AssetsManager::createShape(const Vect2f &size,
                                const Color &color,
                                const Vect2f &pos) {

    AssetID shapeID     = AssetIDGenerator::get();
    mAssets[shapeID] = new Shape(size, color, pos);

    LOG << Log::VERBOSE << ("[AssetsManager::createShape] Shape created ID: " +
                            Data2::int_to_str(shapeID)).c_str() << std::endl;

    return shapeID;
}

AssetID AssetsManager::createText(const std::wstring &text,
                               const unsigned int &fontSize,
                               const AssetID &font) {

    AssetID textID     = AssetIDGenerator::get();
    mAssets[textID] = new Text();
    static_cast<Text*>(mAssets[textID])->setFont(*getAsset<Font>(font));
    static_cast<Text*>(mAssets[textID])->setFontSize(fontSize);
    static_cast<Text*>(mAssets[textID])->setString(text);

    LOG << Log::VERBOSE << ("[AssetsManager::createText] Text created ID: " +
                            Data2::int_to_str(textID)).c_str() << std::endl;

    return textID;
}

AssetsManager::~AssetsManager() {
    LOG << Log::VERBOSE
        << "[AssetsManager::~AssetsManage] Cleaning everything..."
        << std::endl;

    for (unsigned int i = 0; i < mAssets.size(); i++) {
        delete mAssets.at(i);
    }
    mAssets.clear();
}
