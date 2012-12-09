#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H
#include "debugger.h"
#include "engine_config.h"
#include "converter.h"
#include "cfgparser.h"

namespace ME{

class AssetsManager
{
public:
    static AssetsManager * getInstance();
    ~AssetsManager();

    // LoadAsset
    Image* loadAssetImage(const std::string &name, const std::string &fileName, load_type loadType = NOW);
    Music* loadAssetMusic(const std::string &name, const std::string &fileName, load_type loadType = NOW);
    Texture* loadAssetTexture(const std::string &name, const std::string &fileName, load_type loadType = NOW);
    Sprite* loadAssetSprite(const std::string &name, const Sprite &sprite, load_type loadType = NOW);
    Sound* loadAssetSound(const std::string &name, const std::string &fileName, load_type loadType = NOW);
    CFGParser* loadAssetCFGParser(const std::string &name, const std::string &fileName, load_type loadType = NOW);
    Font* loadAssetFont(const std::string &name, const std::string &fileName, load_type loadType = NOW);
    RectangleShape* loadAssetRectangle(const std::string &name,  const float & width,const float &height, load_type loadType = NOW);



    //GetAsset
    // return null if not found
    Texture* getAssetTexture(const std::string &name);
    Sprite* getAssetSprite(const std::string &name);
    Sound* getAssetSound(const std::string &name);
    Music* getAssetMusic(const std::string &name);
    Image* getAssetImage(const std::string &name);
    CFGParser* getAssetCFGParser(const std::string &name);
    Font* getAssetFont(const std::string &name);
    RectangleShape* getAssetRectangle(const std::string &name);


    // implemente that in the future
    void processQueue();
    int getQueueNumber();


    // return null pointer
    int removeAsset(const std::string &name,files_types type);


private:
    AssetsManager();

    Debugger *dbg;

    bool _processQueue;
    std::queue<std::string> mQueue;
    std::map<std::string, Texture*> mTextures;
    std::map<std::string, Sprite*> mSprites;
    std::map<std::string, Sound*> mSounds;
    std::map<std::string, Music*> mMusic;
    std::map<std::string,Image> mImages;
    std::map<std::string, CFGParser*> mConfigFiles;
    std::map<std::string, Font*> mFonts;
     std::map<std::string, RectangleShape*> mRectangleShapes;

};

}

#endif // ASSETSMANAGER_H
