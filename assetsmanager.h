#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H
#include "debugger.h"
#include "config.h"
#include "TO.h"
#include "cfgparser.h"

namespace ME {

class AssetsManager {
public:
    static AssetsManager* getInstance();
    ~AssetsManager();

    // Carrega da memória
    Image* loadImage(const std::string &name, const std::string &fileName, bool persist = true);
    Music* loadMusic(const std::string &name, const std::string &fileName, bool persist = false);
    Texture* loadTexture(const std::string &name, const std::string &fileName, bool persist = false);
    Sound* loadSound(const std::string &name, const std::string &fileName, bool persist = false);
    Font* loadFont(const std::string &name, const std::string &fileName, bool persist = false);


    // Criação de assets
    RectangleShape* createRectangle(const std::string &name, const float & width, const float &height, bool persist = false);
    Text* createText(const std::string &name, const Text &text, bool persist = false);
    Sprite* createSprite(const std::string &name, const Sprite &sprite, bool persist = false);


    // Retorna um asset como ponteiro ou nullptr
    Texture* getTexture(const std::string &name);
    Sprite* getSprite(const std::string &name);
    Sound* getSound(const std::string &name);
    Music* getMusic(const std::string &name);
    Image* getImage(const std::string &name);
    Font* getFont(const std::string &name);


    RectangleShape* getRectangleShape(const std::string &name);
    Text* getText(const std::string &name);

    // Retorna nullptr
    int remove(const std::string &name, ASSETS_TYPE type);

    void clearNonPersistent();


private:
    std::string ASSETS_PATH;
    AssetsManager();
    static AssetsManager* instace;
    Debugger *dbg;

    std::map<std::string, TextureAsset> mTextures;
    std::map<std::string, SpriteAsset> mSprites;
    std::map<std::string, SoundAsset> mSounds;
    std::map<std::string, MusicAsset> mMusics;
    std::map<std::string, ImageAsset> mImages;
    std::map<std::string, FontAsset> mFonts;

    std::map<std::string, RectangleShapeAsset> mRectangleShapes;
    std::map<std::string, TextAsset> mTexts;
};

}

#endif // ASSETSMANAGER_H
