#include "assetsmanager.h"

using namespace ME;

AssetsManager::AssetsManager() : _processQueue(false)
{
    dbg = Debugger::getInstance();
}

AssetsManager::~AssetsManager(){
    // clear everything
    dbg->log(WARNING,1,"Comecando a desalocar memoria de Assets");

    std::map<std::string, Texture*>::iterator itTexture = mTextures.begin();
    std::map<std::string, Sprite*>::iterator itSprite = mSprites.begin();
    std::map<std::string, Sound*>::iterator itSound = mSounds.begin();
    std::map<std::string, Music*>::iterator itMusic = mMusic.begin();
    std::map<std::string, CFGParser*>::iterator itCFGParser = mConfigFiles.begin();
    std::map<std::string, Font*>::iterator itFonts = mFonts.begin();
    std::map<std::string,RectangleShape*>::iterator itRectangleShape = mRectangleShapes.begin();

    mImages.clear();

    for(; itMusic != mMusic.end();itMusic++){
        delete itMusic->second;
    }

    mMusic.clear();

    for(; itTexture != mTextures.end();itTexture++){
        delete itTexture->second;
    }

    mTextures.clear();

    for(; itSprite != mSprites.end();itSprite++){
        delete itSprite->second;
    }

    mSprites.clear();

    for(; itSound != mSounds.end();itSound++){
        delete itSound->second;
    }

    mSounds.clear();

    for(; itCFGParser != mConfigFiles.end();itCFGParser++){
        delete itCFGParser->second;
    }


    mConfigFiles.clear();

    for(; itFonts != mFonts.end();itFonts++){
        delete itFonts->second;
    }

    mFonts.clear();

    for(; itRectangleShape != mRectangleShapes.end();itRectangleShape++){
        delete itRectangleShape->second;
    }
    mRectangleShapes.clear();

    dbg->log(WARNING,1,"Todos os assets foram liberados");
}

AssetsManager * AssetsManager::getInstance(){
    static AssetsManager * mAssets = new AssetsManager;
    return mAssets;
}

Image* AssetsManager::loadAssetImage(const std::string &name, const std::string &fileName, load_type NOT_WARNING loadType){
    if ( mImages.find(name) != mImages.end()){
        if ( ShowAssetLoadingDebug )
            dbg->log(WARNING,1,("Imagem: [" + name+  "]" + fileName + " ja carregada na memoria, retornando recurso ja alocado").c_str());
        return &mImages[name];
    }

    if ( ShowAssetLoadingDebug )
        dbg->log(WARNING,1,("Carregado image: [" + name+  "]" + fileName).c_str());

    if (  !  mImages[name].loadFromFile(fileName) ){
        dbg->log(WARNING,1,("Não foi possivel abrir a imagem: [" + name+  "]" + fileName).c_str());
    }
    return &mImages[name];
}

Music* AssetsManager::loadAssetMusic(const std::string &name, const std::string &fileName, load_type NOT_WARNING loadType){
    if ( mMusic.find(name) != mMusic.end()){
        if ( ShowAssetLoadingDebug )
            dbg->log(WARNING,1,("Music: [" + name+  "]" + fileName + " ja carregada na memoria, retornando recurso ja alocado").c_str());
        return mMusic[name];
    }
    if ( ShowAssetLoadingDebug )
        dbg->log(WARNING,1,("Carregado musica: "+ fileName).c_str());

    mMusic.insert( std::make_pair(name,new Music) );
    if (  !  mMusic[name]->openFromFile(fileName) ){
        dbg->log(WARNING,1,("Não foi possivel abrir a musica:[" + name+  "]" + fileName).c_str());
    }
    return mMusic[name];
}

Texture* AssetsManager::loadAssetTexture(const std::string &name, const std::string &fileName, load_type NOT_WARNING loadType){
    if ( mTextures.find(name) != mTextures.end()){
        if ( ShowAssetLoadingDebug )
            dbg->log(WARNING,1,("Texture: [" + name+  "]" + fileName + " ja carregada na memoria, retornando recurso ja alocado").c_str());
        return mTextures[name];
    }
    if ( ShowAssetLoadingDebug )
        dbg->log(WARNING,1,("Carregado texture: "+ fileName).c_str());

    mTextures.insert( std::make_pair(name,new Texture));

    if ( ! mTextures[name]->loadFromFile(fileName) ){
        dbg->log(WARNING,1,("Não foi possivel abrir a textura: [" + name+  "]" + fileName).c_str());
    }
    return mTextures[name];
}


Sprite* AssetsManager::loadAssetSprite(const std::string &name, const Sprite &sprite, load_type NOT_WARNING loadType){
    if ( mSprites.find(name) != mSprites.end()){
        if ( ShowAssetLoadingDebug )
            dbg->log(WARNING,1,("Sprite: [" + name+  "] ja carregada na memoria, retornando recurso ja alocado").c_str());
        return mSprites[name];
    }
    if ( ShowAssetLoadingDebug )
        dbg->log(WARNING,1,("Carregado Sprite: "+ name).c_str());

    mSprites.insert( std::make_pair(name,new Sprite(sprite)) );
    return mSprites[name];
}

Sound* AssetsManager::loadAssetSound(const std::string &name, const std::string &fileName, load_type NOT_WARNING loadType){
    if ( mSounds.find(name) != mSounds.end()){
        if ( ShowAssetLoadingDebug )
            dbg->log(WARNING,1,("Sound: [" + name+  "]" + fileName + " ja carregada na memoria, retornando recurso ja alocado").c_str());
        return mSounds[name];
    }
    if ( ShowAssetLoadingDebug )
        dbg->log(WARNING,1,("Carregado Sound: [" + name+  "]" + fileName).c_str());

    sf::SoundBuffer buffer;
    if ( ! buffer.loadFromFile(fileName)){
        dbg->log(WARNING,1,("Não foi possivel abrir o sound: [" + name+  "]" + fileName).c_str());
    }

    mSounds.insert( std::make_pair(name,new Sound) );
    mSounds[name]->setBuffer(buffer);
    return mSounds[name];
}

CFGParser* AssetsManager::loadAssetCFGParser(const std::string &name, const std::string &fileName, load_type NOT_WARNING loadType){
    if ( mConfigFiles.find(name) != mConfigFiles.end()){
        if ( ShowAssetLoadingDebug )
            dbg->log(WARNING,1,("ConfigFile: [" + name+  "]" + fileName + " ja carregada na memoria, retornando recurso ja alocado").c_str());
        return mConfigFiles[name];
    }
    if ( ShowAssetLoadingDebug )
        dbg->log(WARNING,1,("Carregado CFG : [" + name+  "]" + fileName).c_str());

    mConfigFiles.insert(std::make_pair(name,new CFGParser(fileName)));

    return mConfigFiles[name];
}

Font* AssetsManager::loadAssetFont(const std::string &name, const std::string &fileName, load_type NOT_WARNING loadType){
    if ( mFonts.find(name) != mFonts.end()){
        if ( ShowAssetLoadingDebug )
            dbg->log(WARNING,1,("Font: [" + name+  "]" + fileName + " ja carregada na memoria, retornando recurso ja alocado").c_str());
        return mFonts[name];
    }
    if ( ShowAssetLoadingDebug )
            dbg->log(WARNING,1,("Carregado font: [" + name+  "]" + fileName).c_str());

    mFonts.insert( std::make_pair(name,new Font) );

    if (  !mFonts[name]->loadFromFile(fileName)){
        dbg->log(WARNING,1,("Não foi possivel abrir a font: [" + name+  "]" + fileName).c_str());
    }

    return mFonts[name];
}


RectangleShape* AssetsManager::loadAssetRectangle(const std::string &name, const float & width,const float &height, load_type NOT_WARNING loadType){
    if ( mRectangleShapes.find(name) != mRectangleShapes.end()){
        if ( ShowAssetLoadingDebug )
            dbg->log(WARNING,1,("RectangleShape: [" + name+  "]  ja carregada na memoria, retornando recurso ja alocado").c_str());
        return mRectangleShapes[name];
    }
    if ( ShowAssetLoadingDebug )
            dbg->log(WARNING,1,("Criando RectangleShape: [" + name+  "]").c_str());

    mRectangleShapes.insert( std::make_pair(name,new RectangleShape(sf::Vector2f(width,height))));
    return mRectangleShapes[name];
}



Texture* AssetsManager::getAssetTexture(const std::string &name){
    if (mTextures.find(name) != mTextures.end() ){
        return mTextures[name];
    }else{
     dbg->log(CRITICAL,1,("Impossivel encontrar Texture recurso: [" + name+  "]").c_str());
     Texture *tmp = new sf::Texture;
     return tmp;
    }
}

Sprite* AssetsManager::getAssetSprite(const std::string &name){
    if (mSprites.find(name) != mSprites.end() ){
        return mSprites[name];
    }else{
     dbg->log(CRITICAL,1,("Impossivel encontrar Sprite recurso: [" + name+  "]").c_str());
     Sprite *tmp = new sf::Sprite;
     return tmp;
    }
}

Sound* AssetsManager::getAssetSound(const std::string &name){
    if (mSounds.find(name) != mSounds.end() ){
        return mSounds[name];
    }else{
     dbg->log(CRITICAL,1,("Impossivel encontrar Sound recurso: [" + name+  "]").c_str());
     Sound *tmp = NULL;
     return tmp;
    }
}

Music* AssetsManager::getAssetMusic(const std::string &name){
    if (mMusic.find(name) != mMusic.end() ){
        return mMusic[name];
    }else{
     dbg->log(CRITICAL,1,("Impossivel encontrar Music recurso: [" + name+  "]").c_str());
     Music *tmp = new Music;
     return tmp;
    }
}

Image* AssetsManager::getAssetImage(const std::string &name){
    if (mImages.find(name) != mImages.end() ){
        return &mImages[name];
    }else{
     dbg->log(CRITICAL,1,("Impossivel encontrar Image recurso: [" + name+  "]").c_str());
     Image *tmp = new Image;
     return tmp;
    }
}

CFGParser* AssetsManager::getAssetCFGParser(const std::string &name){
    if (mConfigFiles.find(name) != mConfigFiles.end() ){
        return mConfigFiles[name];
    }else{
     dbg->log(CRITICAL,1,("Impossivel encontrar recurso: [" + name+  "]").c_str());
     CFGParser *tmp = new CFGParser;
     return tmp;
    }
}

Font* AssetsManager::getAssetFont(const std::string &name){
    if (mFonts.find(name) != mFonts.end() ){
        return mFonts[name];
    }else{
     dbg->log(CRITICAL,1,("Impossivel encontrar Font recurso: [" + name+  "]").c_str());
     Font *tmp = new Font;
     return tmp;
    }
}



RectangleShape* AssetsManager::getAssetRectangle(const std::string &name){
    if (mRectangleShapes.find(name) != mRectangleShapes.end() ){
        return mRectangleShapes[name];
    }else{
     dbg->log(CRITICAL,1,("Impossivel encontrar RectangleShape recurso: [" + name+  "]").c_str());
     RectangleShape *tmp = new RectangleShape();
     return tmp;
    }
}


int AssetsManager::removeAsset(const std::string &name,files_types type){
    if ( type == IMAGE ){
        std::map<std::string,Image>::iterator p = mImages.find(name);
        if ( mImages.end() != p){
            mImages.erase(p);
        }
    }
    if ( type == MUSIC){
        std::map<std::string,Music*>::iterator p = mMusic.find(name);
        if ( mMusic.end() != p){
            delete mMusic[name];
            mMusic.erase(p);
        }
    }
    if ( type == TEXTURE){
        std::map<std::string,Texture*>::iterator p = mTextures.find(name);
        if ( mTextures.end() != p){
            delete mTextures[name];
            mTextures.erase(p);
        }
    }
    if ( type == SPRITE){
        std::map<std::string,Sprite*>::iterator p = mSprites.find(name);
        if ( mSprites.end() != p){
            delete mSprites[name];
            mSprites.erase(p);
        }
    }
    if ( type == SOUND){
        std::map<std::string,Sound*>::iterator p = mSounds.find(name);
        if ( mSounds.end() != p){
            delete mSounds[name];
            mSounds.erase(p);
        }
    }
    if ( type == CFGPARSER){
        std::map<std::string,CFGParser*>::iterator p = mConfigFiles.find(name);

        if ( mConfigFiles.end() != p){
            delete mConfigFiles[name];
            mConfigFiles.erase(p);
            std::cout << "Found" << std::endl;
        }
    }
    if ( type == FONT){
        std::map<std::string,Font*>::iterator p = mFonts.find(name);
        if ( mFonts.end() != p){
            delete mFonts[name];
            mFonts.erase(p);
        }
    }
    if ( type == RECTANGLESHAPE){
        std::map<std::string,RectangleShape*>::iterator p = mRectangleShapes.find(name);
        if ( mRectangleShapes.end() != p){
            delete mRectangleShapes[name];
            mRectangleShapes.erase(p);
        }
    }

    return 0;
}
