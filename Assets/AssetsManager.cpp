#include "AssetsManager.h"

using namespace ME;

AssetsManager::AssetsManager() {
    LOG << Log::VERBOSE << "[AssetsManager::AssetsManager] AssetsManager created" << std::endl;
}

MEid AssetsManager::loadTexture(const std::string &fileName) {
    MEid textureID     = ID::get();
    mAssets[textureID] = new Texture(fileName);

    LOG << Log::VERBOSE << ("[AssetsManager::loadTexture] Texture loaded ID: " + Data2::int_to_str(textureID)).c_str() << std::endl;

    return textureID;
}

MEid AssetsManager::loadFont(const std::string &fileName) {
    MEid fontID     = ID::get();
    mAssets[fontID] = new Font(fileName);

    LOG << Log::VERBOSE << ("[AssetsManager::loadFont] Font loaded ID: " + Data2::int_to_str(fontID)).c_str() << std::endl;

    return fontID;
}

MEid AssetsManager::loadFont(SM::BYTE* bytes, std::size_t size) {
    MEid fontID     = ID::get();
    mAssets[fontID] = new Font();
    getAsset<Font>(fontID)->loadFromMemory(bytes, size);

    LOG << Log::VERBOSE << ("[AssetsManager::loadFont] Font loaded from memory ID: " + Data2::int_to_str(fontID)).c_str() << std::endl;

    return fontID;
}

MEid AssetsManager::loadMusic(const std::string &fileName) {
    MEid musicID     = ID::get();
    mAssets[musicID] = new Music(fileName);

    LOG << Log::VERBOSE << ("[AssetsManager::loadMusic] Music loaded ID: " + Data2::int_to_str(musicID)).c_str() << std::endl;

    return musicID;
}

MEid AssetsManager::loadSound(const std::string &fileName) {
    MEid soundID     = ID::get();
    mAssets[soundID] = new Sound(fileName);

    LOG << Log::VERBOSE << ("[AssetsManager::loadSound] Sound loaded ID: " + Data2::int_to_str(soundID)).c_str() << std::endl;

    return soundID;
}

MEid AssetsManager::createSprite(const MEid &texture) {
    MEid spriteID     = ID::get();
    mAssets[spriteID] = new Sprite();
   static_cast<Sprite*>(mAssets[spriteID])->setTexture(getAsset<Texture>(texture));

    LOG << Log::VERBOSE << ("[AssetsManager::createSprite] Sprite created ID: " + Data2::int_to_str(spriteID)).c_str() << std::endl;

    return spriteID;
}

MEid AssetsManager::createSpriteAnimation() {
    MEid spriteAnID     = ID::get();
    mAssets[spriteAnID] = new SpriteAnimation();

    LOG << Log::VERBOSE << ("[AssetsManager::createSpriteAnimation] SpriteAnimation created ID: " + Data2::int_to_str(spriteAnID)).c_str() << std::endl;

    return spriteAnID;
}

MEid AssetsManager::createShape(const Vect2f &size, const Color &color, const Vect2f &pos) {
    MEid shapeID     = ID::get();
    mAssets[shapeID] = new Shape(size, color, pos);

    LOG << Log::VERBOSE << ("[AssetsManager::createShape] Shape created ID: " + Data2::int_to_str(shapeID)).c_str() << std::endl;

    return shapeID;
}

MEid AssetsManager::createText(const std::wstring &text, const unsigned int &fontSize, const MEid &font) {
    MEid textID     = ID::get();
    mAssets[textID] = new Text();
    static_cast<Text*>(mAssets[textID])->setFont(*getAsset<Font>(font));
    static_cast<Text*>(mAssets[textID])->setFontSize(fontSize);
    static_cast<Text*>(mAssets[textID])->setString(text);

    LOG << Log::VERBOSE << ("[AssetsManager::createText] Text created ID: " + Data2::int_to_str(textID)).c_str() << std::endl;

    return textID;
}

AssetsManager::~AssetsManager() {
    std::unordered_map<MEid, Asset*>::iterator it = mAssets.begin();

    for (; it != mAssets.end(); it++) {
        delete it->second;
        mAssets.erase(it);
    }
}
