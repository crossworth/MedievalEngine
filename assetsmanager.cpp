#include "assetsmanager.h"

using namespace ME;

AssetsManager::AssetsManager() {
    dbg = Debugger::getInstance();
    dbg->log(VERBOSE, 1,"[AssetsManager::AssetsManager] AssetsManager created");

    ASSETS_PATH = GLOBAL_PATH + "data/assets/";
}

AssetsManager::~AssetsManager() {
    dbg->log(VERBOSE, 1,"[AssetsManager::~AssetsManager] Cleaning everything...");

    std::map<std::string, TextureAsset>::iterator itTextures     = mTextures.begin();
    std::map<std::string, SpriteAsset>::iterator itSprites       = mSprites.begin();
    std::map<std::string, SoundAsset>::iterator itSounds         = mSounds.begin();
    std::map<std::string, MusicAsset>::iterator itMusics         = mMusics.begin();
    std::map<std::string, FontAsset>::iterator itFonts           = mFonts.begin();
    std::map<std::string, ImageAsset>::iterator itImages         = mImages.begin();

    std::map<std::string, RectangleShapeAsset>::iterator itRectangleShapes = mRectangleShapes.begin();
    std::map<std::string, TextAsset>::iterator itTexts                     = mTexts.begin();

    for(; itImages != mImages.end(); itImages++) {
       mImages.erase(itImages);
    }
    mImages.clear();

    for(; itMusics != mMusics.end(); itMusics++) {
        delete itMusics->second.data;
    }
    mMusics.clear();

    for(; itTextures != mTextures.end(); itTextures++) {
        delete itTextures->second.data;
    }
    mTextures.clear();

    for(; itSprites != mSprites.end(); itSprites++) {
        delete itSprites->second.data;
    }
    mSprites.clear();

    for(; itSounds != mSounds.end(); itSounds++) {
        delete itSounds->second.data;
    }
    mSounds.clear();

    for(; itFonts != mFonts.end(); itFonts++) {
        delete itFonts->second.data;
    }
    mFonts.clear();

    for(; itRectangleShapes != mRectangleShapes.end(); itRectangleShapes++) {
        delete itRectangleShapes->second.data;
    }
    mRectangleShapes.clear();

    for(; itTexts != mTexts.end(); itTexts++) {
        delete itTexts->second.data;
    }
    mTexts.clear();

    dbg->log(VERBOSE, 1,"[AssetsManager::~AssetsManager] Memory released");
}

void AssetsManager::clearNonPersistent() {
    std::map<std::string, TextureAsset>::iterator itTextures     = mTextures.begin();
    std::map<std::string, SpriteAsset>::iterator itSprites       = mSprites.begin();
    std::map<std::string, SoundAsset>::iterator itSounds         = mSounds.begin();
    std::map<std::string, MusicAsset>::iterator itMusics         = mMusics.begin();
    std::map<std::string, FontAsset>::iterator itFonts           = mFonts.begin();

    std::map<std::string, RectangleShapeAsset>::iterator itRectangleShape = mRectangleShapes.begin();
    std::map<std::string, TextAsset>::iterator itText                     = mTexts.begin();

    for(; itTextures != mTextures.end(); itTextures++) {
        if (itTextures->second.persist == false) {
            delete itTextures->second.data;
            mTextures.erase(itTextures);
        }
    }

    for(; itSprites != mSprites.end(); itSprites++) {
        if (itSprites->second.persist == false) {
            delete itSprites->second.data;
            mSprites.erase(itSprites);
        }
    }

    for(; itSounds != mSounds.end(); itSounds++) {
        if (itMusics->second.persist == false) {
            delete itSounds->second.data;
            mSounds.erase(itSounds);
        }
    }

    for(; itFonts != mFonts.end(); itFonts++) {
        if (itMusics->second.persist == false) {
            delete itFonts->second.data;
            mFonts.erase(itFonts);
        }
    }

    for(; itRectangleShape != mRectangleShapes.end(); itRectangleShape++) {
        if (itMusics->second.persist == false) {
            delete itRectangleShape->second.data;
            mRectangleShapes.erase(itRectangleShape);
        }
    }

    for(; itText != mTexts.end(); itText++) {
        if (itMusics->second.persist == false) {
            delete itText->second.data;
            mTexts.erase(itText);
        }
    }
}

AssetsManager* AssetsManager::instace = nullptr;

AssetsManager* AssetsManager::getInstance() {
    if(instace == nullptr) {
        instace = new AssetsManager();
    }
    return instace;
}

/*
* Imagens sempre são carregadas de forma persistente, já que pode existir referências desconhecidas.
*
*/
Image* AssetsManager::loadImage(const std::string &name, const std::string &fileName, bool persist) {
    if (mImages.find(name) != mImages.end()) {
        if (DEBUG_LOADING_ASSETS) {
            dbg->log(VERBOSE, 1, ("[AssetsManager::loadImage] Image (" + name +  " - " + fileName + ") NAME already loaded").c_str());
        }

        mImages[name].persist = persist;
        return &mImages[name].data;
    }

    if (!mImages[name].data.loadFromFile(ASSETS_PATH + fileName)) {
        dbg->log(WARNING, 1, ("[AssetsManager::loadImage] Image (" + name +  " - " + fileName + ") error while opening").c_str());
        return nullptr;
    }

    if (DEBUG_LOADING_ASSETS) {
        dbg->log(VERBOSE, 1, ("[AssetsManager::loadImage] Image (" + name +  " - " + fileName + ") loaded").c_str());
    }

    mImages[name].persist = persist;
    return &mImages[name].data;
}

Music* AssetsManager::loadMusic(const std::string &name, const std::string &fileName, bool persist) {
    if (mMusics.find(name) != mMusics.end()) {
        if (DEBUG_LOADING_ASSETS) {
            dbg->log(VERBOSE, 1, ("[AssetsManager::loadMusic] Music (" + name +  " - " + fileName + ") NAME already loaded").c_str());
        }
        mMusics[name].persist = persist;
        return mMusics[name].data;
    }

    mMusics[name].data = new Music;

    if (!mMusics[name].data->openFromFile(ASSETS_PATH + fileName)) {
        dbg->log(WARNING, 1, ("[AssetsManager::loadMusic] Music (" + name +  " - " + fileName + ") error while opening").c_str());
        return nullptr;
    }

    if (DEBUG_LOADING_ASSETS) {
        dbg->log(VERBOSE, 1, ("[AssetsManager::loadMusic] Music (" + name +  " - " + fileName + ") loaded").c_str());
    }

    mMusics[name].persist = persist;
    return mMusics[name].data;
}

Texture* AssetsManager::loadTexture(const std::string &name, const std::string &fileName, bool persist) {
    if (mTextures.find(name) != mTextures.end()) {
        if (DEBUG_LOADING_ASSETS) {
            dbg->log(VERBOSE, 1, ("[AssetsManager::loadTexture] Texture (" + name +  " - " + fileName + ") NAME already loaded").c_str());
        }
        mMusics[name].persist = persist;
        return mTextures[name].data;
    }

    mTextures[name].data = new Texture;

    if (!mTextures[name].data->loadFromFile(ASSETS_PATH + fileName)) {
        dbg->log(WARNING, 1, ("[AssetsManager::loadTexture] Texture (" + name +  " - " + fileName + ") error while opening").c_str());
        return nullptr;
    }

    if (DEBUG_LOADING_ASSETS) {
        dbg->log(VERBOSE, 1, ("[AssetsManager::loadTexture] Texture (" + name +  " - " + fileName + ") loaded").c_str());
    }

    mMusics[name].persist = persist;
    return mTextures[name].data;
}

Sprite* AssetsManager::createSprite(const std::string &name, const Sprite &sprite, bool persist) {
    if (mSprites.find(name) != mSprites.end()) {
        if (DEBUG_LOADING_ASSETS) {
            dbg->log(VERBOSE, 1, ("[AssetsManager::createSprite] Sprite (" + name + ") NAME already loaded").c_str());
        }
        mSprites[name].persist = persist;
        return mSprites[name].data;
    }

    mSprites[name].data = new Sprite(sprite);

    if (DEBUG_LOADING_ASSETS) {
        dbg->log(VERBOSE, 1, ("[AssetsManager::createSprite] Sprite (" + name + ") loaded").c_str());
    }

    mSprites[name].persist = persist;
    return mSprites[name].data;
}

Sound* AssetsManager::loadSound(const std::string &name, const std::string &fileName, bool persist) {
    if (mSounds.find(name) != mSounds.end()) {
        if (DEBUG_LOADING_ASSETS) {
            dbg->log(VERBOSE, 1, ("[AssetsManager::loadSound] Sound (" + name +  " - " + fileName + ") NAME already loaded").c_str());
        }
        mSounds[name].persist = persist;
        return mSounds[name].data;
    }

    sf::SoundBuffer buffer;

    mSounds[name].data = new Sound;
    mSounds[name].data->setBuffer(buffer);

    if (!buffer.loadFromFile(fileName)) {
        dbg->log(WARNING, 1, ("[AssetsManager::loadSound] Sound (" + name +  " - " + fileName + ") error while opening").c_str());
        return nullptr;
    }

    if (DEBUG_LOADING_ASSETS) {
        dbg->log(VERBOSE, 1, ("[AssetsManager::createSprite] Sound (" + name +  " - " + fileName + ") loaded").c_str());
    }

    mSounds[name].persist = persist;
    return mSounds[name].data;
}

Font* AssetsManager::loadFont(const std::string &name, const std::string &fileName, bool persist) {
    if (mFonts.find(name) != mFonts.end()) {
        if (DEBUG_LOADING_ASSETS) {
            dbg->log(VERBOSE, 1, ("[AssetsManager::loadFont] Font (" + name +  " - " + fileName + ") NAME already loaded").c_str());
        }
        mFonts[name].persist = persist;
        return mFonts[name].data;
    }

    mFonts[name].data = new Font;

    if (!mFonts[name].data->loadFromFile(fileName)) {
        dbg->log(WARNING, 1, ("[AssetsManager::loadFont] Font (" + name +  " - " + fileName + ") error while opening").c_str());
        return nullptr;
    }

    if (DEBUG_LOADING_ASSETS) {
        dbg->log(VERBOSE, 1, ("[AssetsManager::loadFont] Font (" + name +  " - " + fileName + ") loaded").c_str());
    }

    mFonts[name].persist = persist;
    return mFonts[name].data;
}


RectangleShape* AssetsManager::createRectangle(const std::string &name, const float &width, const float &height, bool persist) {
    if ( mRectangleShapes.find(name) != mRectangleShapes.end()){
        if (DEBUG_LOADING_ASSETS) {
            dbg->log(VERBOSE, 1, ("[AssetsManager::createRectangle] Rectangle (" + name + ") NAME already loaded").c_str());
        }
        mRectangleShapes[name].persist = persist;
        return mRectangleShapes[name].data;
    }

    mRectangleShapes[name].data = new RectangleShape(sf::Vector2f(width, height));

    if (DEBUG_LOADING_ASSETS) {
        dbg->log(VERBOSE, 1, ("[AssetsManager::createRectangle] Rectangle (" + name + ") loaded").c_str());
    }

    mRectangleShapes[name].persist = persist;
    return mRectangleShapes[name].data;
}

Text* AssetsManager::createText(const std::string &name, const Text &text, bool persist) {
    if (mTexts.find(name) != mTexts.end()) {
        if (DEBUG_LOADING_ASSETS) {
            dbg->log(VERBOSE, 1, ("[AssetsManager::createText] Text (" + name + ") NAME already loaded").c_str());
        }
        mTexts[name].persist = persist;
        return mTexts[name].data;
    }

    mTexts[name].data = new Text(text);

    if (DEBUG_LOADING_ASSETS) {
        dbg->log(VERBOSE, 1, ("[AssetsManager::createText] Text (" + name + ") loaded").c_str());
    }

    mTexts[name].persist = persist;
    return mTexts[name].data;
}


Texture* AssetsManager::getTexture(const std::string &name) {
    if (mTextures.find(name) != mTextures.end()) {
        return mTextures[name].data;
    } else {
        dbg->log(WARNING, 1, ("[AssetsManager::getTexture] Texture (" + name + ") not found").c_str());
        return nullptr;
    }
}

Sprite* AssetsManager::getSprite(const std::string &name) {
    if (mSprites.find(name) != mSprites.end()) {
        return mSprites[name].data;
    } else {
        dbg->log(WARNING, 1, ("[AssetsManager::getSprite] Sprite (" + name + ") not found").c_str());
        return nullptr;
    }
}

Sound* AssetsManager::getSound(const std::string &name) {
    if (mSounds.find(name) != mSounds.end()) {
        return mSounds[name].data;
    } else {
        dbg->log(WARNING, 1, ("[AssetsManager::getSound] Sound (" + name + ") not found").c_str());
        return nullptr;
    }
}

Music* AssetsManager::getMusic(const std::string &name) {
    if (mMusics.find(name) != mMusics.end()) {
        return mMusics[name].data;
    } else {
        dbg->log(WARNING, 1, ("[AssetsManager::getMusic] Music (" + name + ") not found").c_str());
        return nullptr;
    }
}

Image* AssetsManager::getImage(const std::string &name) {
    if (mImages.find(name) != mImages.end()) {
        return &mImages[name].data;
    } else {
        dbg->log(WARNING, 1, ("[AssetsManager::getImage] Image (" + name + ") not found").c_str());
        return nullptr;
    }
}

Font* AssetsManager::getFont(const std::string &name) {
    if (mFonts.find(name) != mFonts.end()) {
        return mFonts[name].data;
    } else {
        dbg->log(WARNING, 1, ("[AssetsManager::getFont] Font (" + name + ") not found").c_str());
        return nullptr;
    }
}

RectangleShape* AssetsManager::getRectangleShape(const std::string &name) {
    if (mRectangleShapes.find(name) != mRectangleShapes.end()) {
        return mRectangleShapes[name].data;
    } else {
        dbg->log(WARNING, 1, ("[AssetsManager::getRectangleShape] RectangleShape (" + name + ") not found").c_str());
        return nullptr;
    }
}

Text* AssetsManager::getText(const std::string &name) {
    if (mTexts.find(name) != mTexts.end()) {
        return mTexts[name].data;
    } else {
        dbg->log(WARNING, 1, ("[AssetsManager::getText] Text (" + name + ") not found").c_str());
        return nullptr;
    }
}

int AssetsManager::remove(const std::string &name, ASSETS_TYPE type) {
    if (type == IMAGE) {
        std::map<std::string, ImageAsset>::iterator itImage = mImages.find(name);
        if (mImages.end() != itImage) {
            mImages.erase(itImage);
        }
    }

    if (type == MUSIC) {
        std::map<std::string, MusicAsset>::iterator itMusic = mMusics.find(name);
        if (mMusics.end() != itMusic) {
            delete itMusic->second.data;
            mMusics.erase(itMusic);
        }
    }

    if (type == TEXTURE) {
        std::map<std::string, TextureAsset>::iterator itTexture = mTextures.find(name);
        if (mTextures.end() != itTexture) {
            delete itTexture->second.data;
            mTextures.erase(itTexture);
        }
    }

    if (type == SPRITE) {
        std::map<std::string, SpriteAsset>::iterator itSprite = mSprites.find(name);
        if (mSprites.end() != itSprite) {
            delete itSprite->second.data;
            mSprites.erase(itSprite);
        }
    }

    if (type == SOUND) {
        std::map<std::string, SoundAsset>::iterator itSound = mSounds.find(name);
        if (mSounds.end() != itSound) {
            delete itSound->second.data;
            mSounds.erase(itSound);
        }
    }

    if (type == FONT) {
        std::map<std::string, FontAsset>::iterator itFont = mFonts.find(name);
        if (mFonts.end() != itFont) {
            delete itFont->second.data;
            mFonts.erase(itFont);
        }
    }

    if (type == RECTANGLESHAPE) {
        std::map<std::string, RectangleShapeAsset>::iterator itRectangleShape = mRectangleShapes.find(name);
        if (mRectangleShapes.end() != itRectangleShape) {
            delete itRectangleShape->second.data;
            mRectangleShapes.erase(itRectangleShape);
        }
    }

    if (type == TEXT) {
        std::map<std::string, TextAsset>::iterator itText = mTexts.find(name);
        if (mTexts.end() != itText) {
            delete itText->second.data;
            mTexts.erase(itText);
        }
    }

    return nullptr;
}



