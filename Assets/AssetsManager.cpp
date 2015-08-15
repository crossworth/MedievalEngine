#include "AssetsManager.h"

using namespace ME;


AssetsManager* AssetsManager::mInstance = nullptr;

AssetsManager* AssetsManager::getInstance() {
    if (!mInstance) {
        mInstance = new AssetsManager;
    }
    return mInstance;
}

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
    static_cast<Sprite*>(mAssets[spriteID])->setTexture(static_cast<Texture*>(getAsset(texture)));

    LOG << Log::VERBOSE << ("[AssetsManager::createSprite] Sprite created ID: " + Data2::int_to_str(spriteID)).c_str() << std::endl;

    return spriteID;
}

MEid AssetsManager::createSpriteAnimation() {
    MEid spriteAnID     = ID::get();
    mAssets[spriteAnID] = new SpriteAnimation();

    LOG << Log::VERBOSE << ("[AssetsManager::createSpriteAnimation] SpriteAnimation created ID: " + Data2::int_to_str(spriteAnID)).c_str() << std::endl;

    return spriteAnID;
}

MEid AssetsManager::createText(const std::string &text, const unsigned int &fontSize, const MEid &font) {
    MEid textID     = ID::get();
    mAssets[textID] = new Text();
    static_cast<Text*>(mAssets[textID])->setFont(*static_cast<Font*>(getAsset(font)));
    static_cast<Text*>(mAssets[textID])->setFontSize(fontSize);
    static_cast<Text*>(mAssets[textID])->setString(text);

    LOG << Log::VERBOSE << ("[AssetsManager::createText] Text created ID: " + Data2::int_to_str(textID)).c_str() << std::endl;

    return textID;
}

Asset* AssetsManager::getAsset(const MEid &id) {
    if (mAssets.find(id) != mAssets.end()) {
        return mAssets[id];
    } else {
        LOG << Log::WARNING << ("[AssetsManager::getAsset] Asset not found ID: " + Data2::int_to_str(id)).c_str() << std::endl;
        return new Asset;
    }
}
