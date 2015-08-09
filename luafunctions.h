#ifndef LUAFUNCTIONS_H
#define LUAFUNCTIONS_H
#include "luaengine.h"
#include "assetsmanager.h"
#include "renderwindow.h"
#include "debugger.h"
#include "config.h"
#include "gameengine.h"

// Verifica o número de argumentos passados
#define checkLuaArgumentsNumber() if ((n = lua_gettop(l)) != need) { \
    Debugger *dbg = Debugger::getInstance(); \
    dbg->log(WARNING, 1, ("[LuaScript::" + std::string(__FUNCTION__) + "] needs " + TO::int_to_str(need) +" arguments, " + TO::int_to_str(n) + " arguments informed").c_str()); \
    return 0; }

#define checkLuaArguments() if (!LuaEngine::assertValue(l, need, __FUNCTION__)) { return 0; }


#define luaLog() Debugger *dbg          = Debugger::getInstance();\
    dbg->log(LUA_VERBOSE, 1, std::string("[LuaFile::call] " + std::string(__FUNCTION__)).c_str());


using namespace ME;

ENGINE_UNUSED static LuaEngine *mLua = LuaEngine::getInstace();


/*
*
* Envia um log para saída padrão ou arquivo de debug
*
* void log(string message)
*
*/
ENGINE_UNUSED static int log(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string logMessage = lua_tostring(l, 1);
    dbg->log(VERBOSE, 1, ("[LuaFile::log] " + logMessage).c_str());
    return 0;
}


/*
*
* Cria um Sprite com base em uma textura previamente carregada
*
* void spriteCreate(string sprite_name, string texture_name)
*
*/
ENGINE_UNUSED static int spriteCreate(lua_State *l) {
    int n    = 0;
    int need = 2;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName  = lua_tostring(l, 1);
    std::string textureName = lua_tostring(l, 2);


    AssetsManager *asset = AssetsManager::getInstance();
    Sprite mSprite;
    asset->createSprite(spriteName, mSprite);
    if (asset->getTexture(textureName) != nullptr) {
        asset->getSprite(spriteName)->setTexture(*asset->getTexture(textureName));
    }
    return 0;
}

/*
*
* Altera ou define a textura de um sprite
*
* void spriteSetTexture(string sprite_name, string texture_name)
*
*/
ENGINE_UNUSED static int spriteSetTexture(lua_State *l) {
    int n    = 0;
    int need = 2;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName  = lua_tostring(l, 1);
    std::string textureName = lua_tostring(l, 2);

    AssetsManager *asset = AssetsManager::getInstance();
    if (asset->getSprite(spriteName) != nullptr) {
        asset->getSprite(spriteName)->setTexture(*asset->getTexture(textureName));
    }
    return 0;
}


/*
*
* Desenha o sprite na tela
*
* void spriteDraw(string name)
*
*/
ENGINE_UNUSED static int spriteDraw(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l, 1);

    AssetsManager *asset         = AssetsManager::getInstance();
    renderWindow * mRenderWindow = renderWindow::getInstance();

    if (asset->getSprite(spriteName) != nullptr) {
        mRenderWindow->draw(*asset->getSprite(spriteName));
    }
    return 0;
}

/*
*
* Rotaciona um sprite
*
* void spriteRotate(string name, float angle)
*
*/
ENGINE_UNUSED static int spriteRotate(lua_State *l) {
    int n    = 0;
    int need = 2;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l, 1);
    float angle            = lua_tonumber(l, 2);

    AssetsManager *asset = AssetsManager::getInstance();
    if (asset->getSprite(spriteName) != nullptr) {
        asset->getSprite(spriteName)->rotate(angle);
    }
    return 0;
}

/*
*
* Retorna a rotação do sprite
*
* float spriteGetRotate(string name)
*
*/
ENGINE_UNUSED static int spriteGetRotation(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName  = lua_tostring(l, 1);

    AssetsManager *asset = AssetsManager::getInstance();
    if (asset->getSprite(spriteName) != nullptr) {
        lua_pushnumber(l, asset->getSprite(spriteName)->getRotation());
    }
    return 1;
}

/*
*
* Move um Sprite
*
* void spriteMove(string name, float x, float y)
*
*/
ENGINE_UNUSED static int spriteMove(lua_State *l) {
    int n    = 0;
    int need = 3;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l, 1);
    float x                = lua_tonumber(l, 2);
    float y                = lua_tonumber(l, 3);

    AssetsManager *asset = AssetsManager::getInstance();
    if (asset->getSprite(spriteName) != nullptr) {
        asset->getSprite(spriteName)->move(x, y);
    }
    return 0;
}

/*
*
* Define a posição de um sprite na tela
*
* void spriteSetPosition(string name, float x, float y)
*
*/
ENGINE_UNUSED static int spriteSetPosition(lua_State *l) {
    int n    = 0;
    int need = 3;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l, 1);
    float x                = lua_tonumber(l, 2);
    float y                = lua_tonumber(l, 3);

    AssetsManager *asset = AssetsManager::getInstance();
    if (asset->getSprite(spriteName) != nullptr) {
        asset->getSprite(spriteName)->setPosition(x,y);
    }
    return 0;
}

/*
*
* Define o sub-retângulo de uma textura de um sprite
*
* void spriteSetRect(string name, float top, float left, float width, float height)
*
*/
ENGINE_UNUSED static int spriteSetRect(lua_State *l) {
    int n    = 0;
    int need = 5;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l, 1);
    float top              = lua_tointeger(l, 2);
    float left             = lua_tointeger(l, 3);
    float width            = lua_tointeger(l, 4);
    float height           = lua_tointeger(l, 5);

    AssetsManager *asset = AssetsManager::getInstance();
    if (asset->getSprite(spriteName) != nullptr) {
      asset->getSprite(spriteName)->setTextureRect(sf::IntRect(left, top, width, height));
    }
    return 0;
}

/*
*
* Retorna a posição de um sprite
*
* table[x, y] spriteGetPosition(string name)
*
*/
ENGINE_UNUSED static int spriteGetPosition(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l, 1);

    AssetsManager *asset = AssetsManager::getInstance();
    sf::Vector2f pos(0.0f, 0.0f);

    if(asset->getSprite(spriteName) != nullptr) {
        pos = asset->getSprite(spriteName)->getPosition();
    }

    lua_newtable(l);
    lua_pushnumber(l, pos.x);
    lua_setfield(l, -2, "x");
    lua_pushnumber(l, pos.y);
    lua_setfield(l, -2, "y");
    return 1;
}

/*
*
* Define a escala de um sprite
*
* void spriteSetScale(string name, float x, float y)
*
*/
ENGINE_UNUSED static int spriteSetScale(lua_State *l) {
    int n    = 0;
    int need = 3;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l, 1);
    float x                = lua_tonumber(l, 2);
    float y                = lua_tonumber(l, 3);

    AssetsManager *asset = AssetsManager::getInstance();
    if(asset->getSprite(spriteName) != nullptr) {
        asset->getSprite(spriteName)->setScale(x, y);
    }
    return 0;
}


/*
*
* Retorna a escala de um sprite
*
* table[x, y] spriteGetScale(string name)
*
*/
ENGINE_UNUSED static int spriteGetScale(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l, 1);

    AssetsManager *asset = AssetsManager::getInstance();
    sf::Vector2f scale(0.0f, 0.0f);

    if (asset->getSprite(spriteName) != nullptr) {
        scale = asset->getSprite(spriteName)->getScale();
    }

    lua_newtable(l);
    lua_pushnumber(l, scale.x);
    lua_setfield(l, -2, "x");
    lua_pushnumber(l, scale.y);
    lua_setfield(l, -2, "y");
    return 1;
}

/*
*
* Define a origem de um sprite
*
* void spriteSetOrigin(string name, float x, float y)
*
*/
ENGINE_UNUSED static int spriteSetOrigin(lua_State *l) {
    int n    = 0;
    int need = 3;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l, 1);
    float x                = lua_tonumber(l, 2);
    float y                = lua_tonumber(l, 3);

    AssetsManager *asset   = AssetsManager::getInstance();

    if (asset->getSprite(spriteName) != nullptr) {
        asset->getSprite(spriteName)->setOrigin(x, y);
    }

    return 0;
}

/*
*
* Retorna a origem de um sprite
*
* table[x, y] spriteGetOrigin(string name)
*
*/
ENGINE_UNUSED static int spriteGetOrigin(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l, 1);
    AssetsManager *asset   = AssetsManager::getInstance();
    sf::Vector2f origin(0.0f, 0.0f);

    if (asset->getSprite(spriteName) != nullptr) {
        origin = asset->getSprite(spriteName)->getOrigin();
    }

    lua_newtable(l);
    lua_pushinteger(l, origin.x);
    lua_setfield(l, -2, "x");
    lua_pushinteger(l, origin.y);
    lua_setfield(l, -2, "y");
    return 1;
}

/*
*
* Define a cor de um sprite
*
* void spriteSetColor(string name, int red, int green, int blue, int alpha optional)
*
*/
ENGINE_UNUSED static int spriteSetColor(lua_State *l) {
    int n    = 0;
    int need = 4;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l,1);

    int r = lua_tointeger(l, 2);
    int g = lua_tointeger(l, 3);
    int b = lua_tointeger(l, 4);
    int a = 255;

    if (lua_gettop(l) == 5) {
        a = lua_tointeger(l, 5);
    }

    AssetsManager *asset = AssetsManager::getInstance();

    if(asset->getSprite(spriteName) != nullptr) {
        asset->getSprite(spriteName)->setColor(sf::Color(r, g, b, a));
    }


    return 0;
}

/*
*
* Retorna a cor de um sprite
*
* table[r, g, b, a] spriteGetColor(string name)
*
*/
ENGINE_UNUSED static int spriteGetColor(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l, 1);
    AssetsManager *asset   = AssetsManager::getInstance();
    sf::Color color(255, 255, 255, 255);

    if(asset->getSprite(spriteName) != nullptr) {
        color = asset->getSprite(spriteName)->getColor();
    }

    lua_newtable(l);
    lua_pushinteger(l, color.r);
    lua_setfield(l, -2, "r");
    lua_pushinteger(l, color.g);
    lua_setfield(l, -2, "g");
    lua_pushinteger(l, color.b);
    lua_setfield(l, -2, "b");
    lua_pushinteger(l, color.a);
    lua_setfield(l, -2, "a");
    return 1;
}

/*
*
* Define a escala de um sprite
*
* void spriteScale(string name, int x, int y)
*
*/
ENGINE_UNUSED static int spriteScale(lua_State *l) {
    int n    = 0;
    int need = 3;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l, 1);
    float x                = lua_tonumber(l, 2);
    float y                = lua_tonumber(l, 3);
    AssetsManager *assets  = AssetsManager::getInstance();

    if(assets->getSprite(spriteName) != nullptr) {
       assets->getSprite(spriteName)->scale(sf::Vector2f(x, y));
    }

    return 0;
}

/*
*
* Retorna o bound Global de um sprite
*
* table[height, left, top, width] spriteGetGlobalBounds(string name)
*
*/
ENGINE_UNUSED static int spriteGetGlobalBounds(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l,1);
    AssetsManager *asset   = AssetsManager::getInstance();
    sf::FloatRect globalBounds;

    if(asset->getSprite(spriteName) != nullptr) {
        globalBounds = asset->getSprite(spriteName)->getGlobalBounds();
    }

    lua_newtable(l);
    lua_pushnumber(l, globalBounds.height);
    lua_setfield(l, -2, "height");
    lua_pushnumber(l, globalBounds.left);
    lua_setfield(l, -2, "left");
    lua_pushnumber(l, globalBounds.top);
    lua_setfield(l, -2, "top");
    lua_pushnumber(l, globalBounds.width);
    lua_setfield(l, -2, "width");
    return 1;
}

/*
*
* Retorna o bound local de um sprite
*
* table[height, left, top, width] spriteGetLocalBounds(string name)
*
*/
ENGINE_UNUSED static int spriteGetLocalBounds(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l,1);
    AssetsManager *asset   = AssetsManager::getInstance();
    sf::FloatRect localBounds;

    if(asset->getSprite(spriteName) != nullptr) {
        localBounds = asset->getSprite(spriteName)->getLocalBounds();
    }

    lua_newtable(l);
    lua_pushnumber(l, localBounds.height);
    lua_setfield(l, -2, "height");
    lua_pushnumber(l, localBounds.left);
    lua_setfield(l, -2, "left");
    lua_pushnumber(l, localBounds.top);
    lua_setfield(l, -2, "top");
    lua_pushnumber(l, localBounds.width);
    lua_setfield(l, -2, "width");
    return 1;
}

/*
*
* Retorna o tamanho de um sprite
*
* table[x, y] spriteGetSize(string name)
*
*/
ENGINE_UNUSED static int spriteGetSize(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string spriteName = lua_tostring(l, 1);
    AssetsManager *asset   = AssetsManager::getInstance();
    sf::Vector2u size;

    if(asset->getSprite(spriteName) != nullptr) {
        size = asset->getSprite(spriteName)->getTexture()->getSize();
    }

    lua_newtable(l);
    lua_pushinteger(l, size.x);
    lua_setfield(l, -2, "x");
    lua_pushinteger(l, size.y);
    lua_setfield(l, -2, "y");
    return 1;
}

/*
*
* Carrega uma música do disco
*
* void musicLoad(string name, string fileName, bool persist optional)
*
*/
ENGINE_UNUSED static int musicLoad(lua_State *l) {
    int n    = 0;
    int need = 2;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string musicName = lua_tostring(l, 1);
    std::string fileName  = lua_tostring(l, 2);
    bool persist = false;

    if (lua_gettop(l) == 3) {
        persist = lua_toboolean(l, 3);
    }

    AssetsManager *asset = AssetsManager::getInstance();
    asset->loadMusic(musicName, fileName, persist);
    return 0;
}

/*
*
* Inicia uma música já carregada
*
* void musicPlay(string name)
*
*/
ENGINE_UNUSED static int musicPlay(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string musicName = lua_tostring(l, 1);
    AssetsManager *asset  = AssetsManager::getInstance();

    if(asset->getMusic(musicName) != nullptr) {
        asset->getMusic(musicName)->play();
    }

    return 0;
}

/*
*
* Pausa uma música já carregada
*
* void musicPause(string name)
*
*/
ENGINE_UNUSED static int musicPause(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string musicName = lua_tostring(l, 1);
    AssetsManager *asset  = AssetsManager::getInstance();

    if(asset->getMusic(musicName) != nullptr) {
        asset->getMusic(musicName)->pause();
    }

    return 0;
}

/*
*
* Para uma música já carregada
*
* void musicStop(string name)
*
*/
ENGINE_UNUSED static int musicStop(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string musicName = lua_tostring(l, 1);
    AssetsManager *asset  = AssetsManager::getInstance();

    if(asset->getMusic(musicName) != nullptr) {
        asset->getMusic(musicName)->stop();
    }

    return 0;
}

/*
*
* Retorna se uma música está tocando ou não
*
* bool isPlayingMusic(string name)
*
*/
ENGINE_UNUSED static int isPlayingMusic(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string musicName = lua_tostring(l, 1);
    AssetsManager *asset  = AssetsManager::getInstance();

    if(asset->getMusic(musicName) != nullptr) {
        if (asset->getMusic(musicName)->getStatus() == sf::SoundSource::Playing) {
            lua_pushboolean(l, true);
        } else {
            lua_pushboolean(l, false);
        }
    }

    return 1;
}

/*
*
* Retorna a duração da música em segundos
*
* int musicGetDuration(string name)
*
*/
ENGINE_UNUSED static int musicGetDuration(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string musicName = lua_tostring(l, 1);
    AssetsManager *asset  = AssetsManager::getInstance();
    sf::Time duration;

    if(asset->getMusic(musicName) != nullptr) {
        duration = asset->getMusic(musicName)->getDuration();
    }

    lua_pushnumber(l, duration.asSeconds());

    return 1;
}

/*
*
* Retorna a duração da música em segundos
*
* float musicGetVolume(string name)
*
*/
ENGINE_UNUSED static int musicGetVolume(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string musicName = lua_tostring(l,1);
    AssetsManager *asset  = AssetsManager::getInstance();
    float volume          = 0.0f;

    if (asset->getMusic(musicName) != nullptr) {
        volume = asset->getMusic(musicName)->getVolume();
    }

    lua_pushnumber(l, volume);
    return 1;
}

/*
*
* Define o volume da música
*
* void musicSetVolume(string name, float volume)
*
*/
ENGINE_UNUSED static int musicSetVolume(lua_State *l) {
    int n    = 0;
    int need = 2;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string musicName = lua_tostring(l, 1);
    float volume          = lua_tonumber(l, 2);
    AssetsManager *asset  = AssetsManager::getInstance();

    if(asset->getMusic(musicName) != nullptr) {
        asset->getMusic(musicName)->setVolume(volume);
    }

    return 0;
}

/*
*
* Define a posição da música em segundos
*
* void musicSetPlayingOffset(string name, int seconds)
*
*/
ENGINE_UNUSED static int musicSetPlayingOffset(lua_State *l) {
    int n    = 0;
    int need = 2;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string musicName = lua_tostring(l, 1);
    float offSet          = lua_tonumber(l, 2);
    AssetsManager *asset  = AssetsManager::getInstance();

    if (asset->getMusic(musicName) != nullptr) {
        asset->getMusic(musicName)->setPlayingOffset(sf::Time(sf::seconds(offSet)));
    }

    return 0;
}


/*
*
* Consegue a posição da música em segundos
*
* int musicGetPlayingOffset(string name)
*
*/
ENGINE_UNUSED static int musicGetPlayingOffset(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string musicName = lua_tostring(l,1);
    AssetsManager *asset  = AssetsManager::getInstance();
    float pos             = 0.0f;

    if (asset->getMusic(musicName) != nullptr) {
        pos = asset->getMusic(musicName)->getPlayingOffset().asSeconds();
    }

    lua_pushnumber(l, pos);
    return 1;
}

/*
*
* Consegue a posição global do mouse
*
* table[x, y] getMouseGlobalPosition(void)
*
*/
ENGINE_UNUSED static int getMouseGlobalPosition(lua_State *l) {
    int n    = 0;
    int need = 0;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    sf::Vector2i pos  = sf::Mouse::getPosition();
    lua_newtable(l);
    lua_pushinteger(l, pos.x);
    lua_setfield(l, -2, "x");
    lua_pushinteger(l, pos.y);
    lua_setfield(l, -2, "y");
    return 1;
}

/*
*
* Consegue a posição local do mouse
*
* table[x, y] getMouseLocalPosition(void)
*
*/
ENGINE_UNUSED static int getMouseLocalPosition(lua_State *l) {
    int n    = 0;
    int need = 0;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    renderWindow * mRenderWindow = renderWindow::getInstance();
    sf::Vector2i pos             = sf::Mouse::getPosition(*(mRenderWindow->getRenderWindow()));
    lua_newtable(l);
    lua_pushinteger(l, pos.x);
    lua_setfield(l, -2, "x");
    lua_pushinteger(l, pos.y);
    lua_setfield(l, -2, "y");
    return 1;
}

/*
*
* Retorna informações da janela
*
* table[width, height, bitsPerPixel, fullScreen] getWindowInfo(void)
*
*/
ENGINE_UNUSED static int getWindowInfo(lua_State *l) {
    int n    = 0;
    int need = 0;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    renderWindow *mRenderWindow = renderWindow::getInstance();
    windowInformation infos     = mRenderWindow->getWindowInformation();
    lua_newtable(l);
    lua_pushinteger(l, infos.width);
    lua_setfield(l, -2, "width");
    lua_pushinteger(l, infos.height);
    lua_setfield(l, -2, "height");
    lua_pushinteger(l, infos.bitsPerPixel);
    lua_setfield(l, -2, "bitsPerPixel");
    lua_pushinteger(l, infos.fullScreen);
    lua_setfield(l, -2, "fullScreen");
    return 1;
}

/*
*
* Define a câmera da janela
*
* void cameraSet(string name)
*
*/
ENGINE_UNUSED static int cameraSet(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

     std::string cameraName      = lua_tostring(l, 1);
     renderWindow *mRenderWindow = renderWindow::getInstance();
     mRenderWindow->setCamera(cameraName);
     return 0;
}

/*
*
* Move a câmera, aceita o valor "default"
*
* void cameraMove(string name, int x, int y)
*
*/
ENGINE_UNUSED static int cameraMove(lua_State *l) {
    int n    = 0;
    int need = 3;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string cameraName      = lua_tostring(l, 1);
    float x                     = lua_tonumber(l, 2);
    float y                     = lua_tonumber(l, 3);
    renderWindow *mRenderWindow = renderWindow::getInstance();

    if (cameraName == "default") {
        mRenderWindow->getDefaultCamera()->move(x, y);
   } else {
        if(mRenderWindow->getCamera(cameraName) != nullptr) {
            mRenderWindow->getCamera(cameraName)->move(x, y);
        }
    }

    return 0;
}

/*
*
* Cria uma nova câmera, aceita default como tipo para criar uma câmera com tamanho da câmera padrão
* tipo = default, custom
*
* void cameraCreate(string name, string tipo, int width, int height, int top, int left)
*
*/
ENGINE_UNUSED static int cameraCreate(lua_State *l) {
    int n    = 0;
    int need = 2;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string cameraName = lua_tostring(l, 1);
    std::string cameraTipo = lua_tostring(l, 2);

    renderWindow *mRenderWindow = renderWindow::getInstance();

    if (cameraTipo == "default") {
        mRenderWindow->createCamera(cameraName, *mRenderWindow->getDefaultCamera());
    }else{
        float width  = mRenderWindow->getRenderWindow()->getDefaultView().getViewport().width;
        float height = mRenderWindow->getRenderWindow()->getDefaultView().getViewport().height;
        float top    = mRenderWindow->getRenderWindow()->getDefaultView().getViewport().top;
        float left   = mRenderWindow->getRenderWindow()->getDefaultView().getViewport().left;
        width        = lua_tonumber(l, 3);
        height       = lua_tonumber(l, 4);
        top          = lua_tonumber(l, 5);
        left         = lua_tonumber(l, 6);
        mRenderWindow->createCamera(cameraName,sf::FloatRect(left, top, width, height));
    }
    return 0;
}

/*
*
* Define a rotação de uma câmera, aceita default
*
* void cameraSetRotation(string name, float angle)
*
*/
ENGINE_UNUSED static int cameraSetRotation(lua_State *l) {
    int n    = 0;
    int need = 2;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string cameraName = lua_tostring(l, 1);
    float angle            = lua_tonumber(l, 2);

    renderWindow *mRenderWindow = renderWindow::getInstance();

    if(mRenderWindow->getCamera(cameraName) != nullptr) {
        mRenderWindow->getCamera(cameraName)->setRotation(angle);
    }

    return 0;
}

/*
*
* Define o zoom de uma câmera
*
* void cameraZoom(string name, float factor)
*
*/
ENGINE_UNUSED static int cameraZoom(lua_State *l) {
    int n    = 0;
    int need = 2;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string cameraName      = lua_tostring(l, 1);
    float factor                = lua_tonumber(l, 2);
    renderWindow *mRenderWindow = renderWindow::getInstance();

    if (mRenderWindow->getCamera(cameraName) != nullptr) {
        mRenderWindow->getCamera(cameraName)->zoom(factor);
    }

    return 0;
}

/*
*
* Rotaciona uma câmera
*
* void cameraRotate(string name, float angle)
*
*/
ENGINE_UNUSED static int cameraRotate(lua_State *l) {
    int n    = 0;
    int need = 2;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string cameraName      = lua_tostring(l, 1);
    float angle                 = lua_tonumber(l, 2);
    renderWindow *mRenderWindow = renderWindow::getInstance();

    if (mRenderWindow->getCamera(cameraName) != nullptr) {
        mRenderWindow->getCamera(cameraName)->rotate(angle);
    }

    return 0;
}

/*
*
* Reseta a câmera para tamanhos da câmera padrão
*
* void cameraReset(string name)
*
*/
ENGINE_UNUSED static int cameraReset(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();


    std::string cameraName      = lua_tostring(l, 1);
    renderWindow *mRenderWindow = renderWindow::getInstance();

    if(mRenderWindow->getCamera(cameraName)) {
        mRenderWindow->getCamera(cameraName)->reset(sf::FloatRect(0, 0, mRenderWindow->getWindowInformation().width, mRenderWindow->getWindowInformation().height));
    }

    return 0;
}

/*
*
* Define a câmera padrão como ativa
*
* void cameraSetDefault()
*
*/
ENGINE_UNUSED static int cameraSetDefault(lua_State *l) {
    int n    = 0;
    int need = 0;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    renderWindow *mRenderWindow = renderWindow::getInstance();
    mRenderWindow->setCamera(*mRenderWindow->getDefaultCamera());
    return 0;
}

/*
*
* Retorna a rotação da câmera
*
* float cameraGetRotation(string name)
*
*/
ENGINE_UNUSED static int cameraGetRotation(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string cameraName      = lua_tostring(l, 1);
    renderWindow *mRenderWindow = renderWindow::getInstance();
    float angle                 = 0.0f;

    if (mRenderWindow->getCamera(cameraName) != nullptr) {
        angle = mRenderWindow->getCamera(cameraName)->getRotation();
    }

    lua_pushnumber(l, angle);
    return 1;
}

/*
*
* Retorna a posição de uma câmera
*
* table[x, y] cameraGetPosition(string name)
*
*/
ENGINE_UNUSED static int cameraGetPosition(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string cameraName      = lua_tostring(l, 1);
    renderWindow *mRenderWindow = renderWindow::getInstance();
    sf::Vector2f view(0.0f, 0.0f);

    if (mRenderWindow->getCamera(cameraName) != nullptr) {
        view = mRenderWindow->getCamera(cameraName)->getCenter();
    }

    lua_newtable(l);
    lua_pushnumber(l, view.x);
    lua_setfield(l, -2, "x");
    lua_pushnumber(l, view.y);
    lua_setfield(l, -2, "y");
    return 1;
}

ENGINE_UNUSED static int rectangleCreate(lua_State *l) {
    int n    = 0;
    int need = 4;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l, 1);
    float width               = lua_tonumber(l, 2);
    float height              = lua_tonumber(l, 3);
    bool persist              = lua_toboolean(l, 4);
    AssetsManager *assets     = AssetsManager::getInstance();

    assets->createRectangle(rectangleName, width, height, persist);
    return 0;
}

ENGINE_UNUSED static int rectangleSetPosition(lua_State *l) {
    int n    = 0;
    int need = 3;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l, 1);
    float x                   = lua_tonumber(l, 2);
    float y                   = lua_tonumber(l, 3);
    AssetsManager *assets     = AssetsManager::getInstance();
    assets->getRectangleShape(rectangleName)->setPosition(x,y);
    return 0;
}


ENGINE_UNUSED static int rectangleSetFillColor(lua_State *l) {
    int n    = 0;
    int need = 4;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    int r = lua_tointeger(l,2);
    int g = lua_tointeger(l,3);
    int b = lua_tointeger(l,4);
    int a = 255;
    if ( lua_gettop(l) == 5 )
        a = lua_tointeger(l,5);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getRectangleShape(rectangleName)->setFillColor(sf::Color(r,g,b,a));
    return 0;
}


ENGINE_UNUSED static int rectangleDraw(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);

    AssetsManager *assets  = AssetsManager::getInstance();
    renderWindow *mWindow  = renderWindow::getInstance();
    mWindow->draw(*assets->getRectangleShape(rectangleName));
    return 0;
}


ENGINE_UNUSED static int rectangleSetOutlineColor(lua_State *l) {
    int n    = 0;
    int need = 4;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    int r = lua_tointeger(l,2);
    int g = lua_tointeger(l,3);
    int b = lua_tointeger(l,4);
    int a = 255;
    if ( lua_gettop(l) == 5 )
        a = lua_tointeger(l,5);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getRectangleShape(rectangleName)->setOutlineColor(sf::Color(r,g,b,a));
    return 0;
}


ENGINE_UNUSED static int rectangleSetOutlineThickness(lua_State *l) {
    int n    = 0;
    int need = 2;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    float factor = lua_tonumber(l,2);

    AssetsManager *assets = AssetsManager::getInstance();
    assets->getRectangleShape(rectangleName)->setOutlineThickness(factor);
    return 0;
}


ENGINE_UNUSED static int rectangleSetOrigin(lua_State *l) {
    int n    = 0;
    int need = 3;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    float x = lua_tonumber(l,2);
    float y = lua_tonumber(l,3);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getRectangleShape(rectangleName)->setOrigin(sf::Vector2f(x,y));
    return 0;
}

ENGINE_UNUSED static int rectangleSetRotation(lua_State *l) {
    int n    = 0;
    int need = 2;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    float angle = lua_tonumber(l,2);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getRectangleShape(rectangleName)->setRotation(angle);
    return 0;
}


ENGINE_UNUSED static int rectangleSetScale(lua_State *l) {
    int n    = 0;
    int need = 3;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    float x = lua_tonumber(l,2);
    float y = lua_tonumber(l,3);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getRectangleShape(rectangleName)->setScale(sf::Vector2f(x,y));
    return 0;
}

ENGINE_UNUSED static int rectangleSetSize(lua_State *l) {
    int n    = 0;
    int need = 3;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    float w = lua_tonumber(l,2);
    float h = lua_tonumber(l,3);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getRectangleShape(rectangleName)->setSize(sf::Vector2f(w,h));
    return 0;
}



ENGINE_UNUSED static int rectangleSetTexture(lua_State *l) {
    int n    = 0;
    int need = 2;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    std::string textureName = lua_tostring(l,2);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getRectangleShape(rectangleName)->setTexture(assets->loadTexture(rectangleName,textureName));
    return 0;
}



ENGINE_UNUSED static int rectangleGetPosition(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::Vector2f pos  = assets->getRectangleShape(rectangleName)->getPosition();
    lua_newtable(l);
    lua_pushnumber(l,pos.x);
    lua_setfield(l,-2,"x");
    lua_pushnumber(l,pos.y);
    lua_setfield(l,-2,"y");
    return 1;
}


ENGINE_UNUSED static int rectangleGetFillColor(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::Color c  = assets->getRectangleShape(rectangleName)->getFillColor();
    lua_newtable(l);
    lua_pushnumber(l,c.r);
    lua_setfield(l,-2,"r");
    lua_pushnumber(l,c.g);
    lua_setfield(l,-2,"g");
    lua_pushnumber(l,c.b);
    lua_setfield(l,-2,"b");
    lua_pushnumber(l,c.a);
    lua_setfield(l,-2,"a");
    return 1;
}


ENGINE_UNUSED static int rectangleGetOutlineColor(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::Color c  = assets->getRectangleShape(rectangleName)->getOutlineColor();
    lua_newtable(l);
    lua_pushnumber(l,c.r);
    lua_setfield(l,-2,"r");
    lua_pushnumber(l,c.g);
    lua_setfield(l,-2,"g");
    lua_pushnumber(l,c.b);
    lua_setfield(l,-2,"b");
    lua_pushnumber(l,c.a);
    lua_setfield(l,-2,"a");
    return 1;
}



ENGINE_UNUSED static int rectangleGetOutlineThickness(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    float thickness = assets->getRectangleShape(rectangleName)->getOutlineThickness();
    lua_pushnumber(l,thickness);
    return 1;
}

ENGINE_UNUSED static int rectangleGetGlobalBounds(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::FloatRect globalBounds = assets->getRectangleShape(rectangleName)->getGlobalBounds();

    lua_newtable(l);
    lua_pushnumber(l,globalBounds.height);
    lua_setfield(l,-2,"height");
    lua_pushnumber(l,globalBounds.left);
    lua_setfield(l,-2,"left");
    lua_pushnumber(l,globalBounds.top);
    lua_setfield(l,-2,"top");
    lua_pushnumber(l,globalBounds.width);
    lua_setfield(l,-2,"width");
    return 1;
}


ENGINE_UNUSED static int rectangleGetLocalBounds(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::FloatRect localBounds = assets->getRectangleShape(rectangleName)->getLocalBounds();

    lua_newtable(l);
    lua_pushnumber(l,localBounds.height);
    lua_setfield(l,-2,"height");
    lua_pushnumber(l,localBounds.left);
    lua_setfield(l,-2,"left");
    lua_pushnumber(l,localBounds.top);
    lua_setfield(l,-2,"top");
    lua_pushnumber(l,localBounds.width);
    lua_setfield(l,-2,"width");
    return 1;
}



ENGINE_UNUSED static int rectangleGetOrigin(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::Vector2f origin = assets->getRectangleShape(rectangleName)->getOrigin();
    lua_newtable(l);
    lua_pushnumber(l,origin.x);
    lua_setfield(l,-2,"x");
    lua_pushnumber(l,origin.y);
    lua_setfield(l,-2,"y");
    return 1;
}


ENGINE_UNUSED static int rectangleGetRotation(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    float angle = assets->getRectangleShape(rectangleName)->getRotation();
    lua_pushnumber(l,angle);
    return 1;
}

ENGINE_UNUSED static int rectangleGetScale(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::Vector2f scale = assets->getRectangleShape(rectangleName)->getScale();
    lua_newtable(l);
    lua_pushnumber(l,scale.x);
    lua_setfield(l,-2,"x");
    lua_pushnumber(l,scale.y);
    lua_setfield(l,-2,"y");
    return 1;
}


ENGINE_UNUSED static int rectangleGetSize(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::Vector2f size = assets->getRectangleShape(rectangleName)->getSize();
    lua_newtable(l);
    lua_pushnumber(l,size.x);
    lua_setfield(l,-2,"x");
    lua_pushnumber(l,size.y);
    lua_setfield(l,-2,"y");
    return 1;
}



ENGINE_UNUSED static int rectangleMove(lua_State *l) {
    int n    = 0;
    int need = 3;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    float x = lua_tonumber(l,2);
    float y = lua_tonumber(l,3);

    AssetsManager *assets = AssetsManager::getInstance();
    assets->getRectangleShape(rectangleName)->move(sf::Vector2f(x,y));
    return 0;
}


ENGINE_UNUSED static int rectangleRotate(lua_State *l) {
    int n    = 0;
    int need = 2;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    float angle = lua_tonumber(l,2);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getRectangleShape(rectangleName)->rotate(angle);
    return 0;
}

ENGINE_UNUSED static int rectangleScale(lua_State *l) {
    int n    = 0;
    int need = 3;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    std::string rectangleName = lua_tostring(l,1);
    float x = lua_tonumber(l,2);
    float y = lua_tonumber(l,2);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getRectangleShape(rectangleName)->scale(sf::Vector2f(x,y));
    return 0;
}













ENGINE_UNUSED static int isKeyPress(lua_State *l) {
    int n    = 0;
    int need = 1;
    luaLog();
    checkLuaArgumentsNumber();
    checkLuaArguments();

    ME::KEY key;

    if (!lua_isnumber(l, 1)) {
        key = TO::str_to_KEY(lua_tostring(l, 1));
    } else {
        key = (ME::KEY)lua_tointeger(l, 1);
    }

    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key)) {
        lua_pushboolean(l, true);
    } else {
        lua_pushboolean(l, false);
    }

    return 1;
}





void registerFunctions();



#endif // LUAFUNCTIONS_H
