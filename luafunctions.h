#ifndef LUAFUNCTIONS_H
#define LUAFUNCTIONS_H
#include "lua.h"
#include "assetsmanager.h"
#include "renderwindow.h"
#include "debugger.h"
#include "engine_config.h"
#include "gameengine.h"


using namespace ME;

//AssetsManager *asset = AssetsManager::getInstance();
NOT_WARNING static Lua *mLua = Lua::getInstace();


NOT_WARNING static int log(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need ){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao log usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n) + "] argumentos passados.").c_str() );
        return 0;
    }

    Debugger *dbg = Debugger::getInstance();
    if  ( !Lua::assertValue(l,need,__FUNCTION__) ){
        return 0;
    }

    std::string r = lua_tostring(l,1);
    dbg->log(WARNING,1,r.c_str());
    return 0;
}


NOT_WARNING static int spriteLoad(lua_State *l){
    int n = 0;
    int need = 2;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteLoad  usa "+ Converter::int_to_str(need) +" argumento ["+Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string name = lua_tostring(l,1);
    std::string fileName = lua_tostring(l,2);
    AssetsManager *asset = AssetsManager::getInstance();
    Sprite spt;
    asset->loadAssetSprite(name,spt);
    asset->getAssetSprite(name)->setTexture(*asset->loadAssetTexture(fileName,fileName));
    return 0;
}

NOT_WARNING static int spriteLoadFromTexture(lua_State *l){
    int n = 0;
    int need = 2;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteLoadFromTexture  usa "+ Converter::int_to_str(need) +" argumento ["+Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string name = lua_tostring(l,1);
    std::string textureName = lua_tostring(l,2);
    AssetsManager *asset = AssetsManager::getInstance();
    Sprite spt;
    asset->loadAssetSprite(name,spt);
    asset->getAssetSprite(name)->setTexture(*asset->getAssetTexture(textureName));
    return 0;
}



NOT_WARNING static int spriteDraw(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteDraw usa "+ Converter::int_to_str(need) +" argumento ["+Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string name = lua_tostring(l,1);
    AssetsManager *asset = AssetsManager::getInstance();
    renderWindow * mRenderWindow = renderWindow::getInstance();
    mRenderWindow->draw(*asset->getAssetSprite(name));
    return 0;
}


NOT_WARNING static int spriteRotate(lua_State *l){

    int n = 0;
    int need = 2;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteRotate usa "+ Converter::int_to_str(need) +" argumento ["+Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string sptName = lua_tostring(l,1);

    float angle = lua_tonumber(l,2);
    AssetsManager *asset = AssetsManager::getInstance();
    asset->getAssetSprite(sptName)->rotate(angle);
    return 0;
}

NOT_WARNING static int spriteGetRotate(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteGetRotate usa "+ Converter::int_to_str(need) +" argumento ["+Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string sptName = lua_tostring(l,1);
    AssetsManager *asset = AssetsManager::getInstance();
    lua_pushnumber(l,asset->getAssetSprite(sptName)->getRotation());
    return 1;
}

NOT_WARNING static int spriteMove(lua_State *l){
    int n = 0;
    int need = 3;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteMove usa "+ Converter::int_to_str(need) +" argumento ["+Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string sptName = lua_tostring(l,1);
    float x = lua_tonumber(l,2);
    float y = lua_tonumber(l,3);
    AssetsManager *asset = AssetsManager::getInstance();
    asset->getAssetSprite(sptName)->move(x,y);
    return 0;
}


NOT_WARNING static int spriteSetPosition(lua_State *l){
    int n = 0;
    int need = 3;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteSetPosition usa "+ Converter::int_to_str(need) +" argumento ["+Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string sptName = lua_tostring(l,1);
    float x = lua_tonumber(l,2);
    float y = lua_tonumber(l,3);
    AssetsManager *asset = AssetsManager::getInstance();
    asset->getAssetSprite(sptName)->setPosition(x,y);
    return 0;
}

NOT_WARNING static int spriteGetPosition(lua_State *l){
    AssetsManager *asset = AssetsManager::getInstance();

    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteGetPosition usa "+ Converter::int_to_str(need) +" argumento ["+Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string sptName = lua_tostring(l,1);


    sf::Vector2f pos = asset->getAssetSprite(sptName)->getPosition();

    lua_newtable(l);
    lua_pushnumber(l,pos.x);
    lua_setfield(l, -2, "x");
    lua_pushnumber(l,pos.y);
    lua_setfield(l, -2, "y");
    return 1;
}



NOT_WARNING static int spriteSetScale(lua_State *l){
    int n = 0;
    int need = 3;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteSetScale usa "+ Converter::int_to_str(need) +" argumento ["+Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string sptName = lua_tostring(l,1);
    float x = lua_tonumber(l,2);
    float y = lua_tonumber(l,3);
    AssetsManager *asset = AssetsManager::getInstance();
    asset->getAssetSprite(sptName)->setScale(x,y);
    return 0;
}

NOT_WARNING static int spriteGetScale(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteGetScale usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string sptName = lua_tostring(l,1);
    AssetsManager *asset = AssetsManager::getInstance();
    sf::Vector2f scale = asset->getAssetSprite(sptName)->getScale();

    lua_newtable(l);
    lua_pushnumber(l,scale.x);
    lua_setfield(l, -2, "x");
    lua_pushnumber(l,scale.y);
    lua_setfield(l, -2, "y");
    return 1;
}



NOT_WARNING static int spriteSetOrigin(lua_State *l){
    int n = 0;
    int need = 3;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteSetOrigin usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string sptName = lua_tostring(l,1);
    AssetsManager *asset = AssetsManager::getInstance();
    float x =  lua_tonumber(l,2);
    float y = lua_tonumber(l,3);
    asset->getAssetSprite(sptName)->setOrigin(x,y);
    return 0;
}


NOT_WARNING static int spriteGetOrigin(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteGetOrigin usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string sptName = lua_tostring(l,1);
    AssetsManager *asset = AssetsManager::getInstance();
    sf::Vector2f origin = asset->getAssetSprite(sptName)->getOrigin();
    lua_newtable(l);
    lua_pushinteger(l,origin.x);
    lua_setfield(l,-2,"x");
    lua_pushinteger(l,origin.y);
    lua_setfield(l,-2,"y");
    return 1;
}


NOT_WARNING static int spriteSetColor(lua_State *l){
    int n = 0;
    int need = 4;
    if  ( ( n =lua_gettop(l)) < need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteSetColor usa "+ Converter::int_to_str(need) +"( +1 opcional para valor do alpha) argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string sptName = lua_tostring(l,1);

    int r = lua_tointeger(l,2);
    int g = lua_tointeger(l,3);
    int b = lua_tointeger(l,4);
    int a = -1;

    if ( lua_gettop(l) == 5)
        a = lua_tointeger(l,5);
    else
        a = 255;

    AssetsManager *asset = AssetsManager::getInstance();
    asset->getAssetSprite(sptName)->setColor(sf::Color(r,g,b,a));
    return 0;
}


NOT_WARNING static int spriteGetColor(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteGetColor usa "+ Converter::int_to_str(need) +"argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string sptName = lua_tostring(l,1);
    AssetsManager *asset = AssetsManager::getInstance();
    sf::Color color = asset->getAssetSprite(sptName)->getColor();
    lua_newtable(l);
    lua_pushinteger(l,color.r);
    lua_setfield(l, -2, "r");
    lua_pushinteger(l,color.g);
    lua_setfield(l, -2, "g");
    lua_pushinteger(l,color.b);
    lua_setfield(l, -2, "b");
    lua_pushinteger(l,color.a);
    lua_setfield(l, -2, "a");
    return 1;
}


NOT_WARNING static int spriteScale(lua_State *l){
    int n = 0;
    int need = 3;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteScale usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string name = lua_tostring(l,1);
    float x = lua_tonumber(l,2);
    float y = lua_tonumber(l,2);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getAssetSprite(name)->scale(sf::Vector2f(x,y));
    return 0;
}


NOT_WARNING static int spriteGetGlobalBounds(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteGetGlobalBounds usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string sptName = lua_tostring(l,1);

    AssetsManager *asset = AssetsManager::getInstance();
    sf::FloatRect globalBounds = asset->getAssetSprite(sptName)->getGlobalBounds();
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


NOT_WARNING static int spriteGetLocalBounds(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteGetLocalBounds usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string sptName = lua_tostring(l,1);

    AssetsManager *asset = AssetsManager::getInstance();
    sf::FloatRect localBounds = asset->getAssetSprite(sptName)->getLocalBounds();
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



NOT_WARNING static int spriteGetSize(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao spriteGetSize usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string sptName = lua_tostring(l,1);

    AssetsManager *asset = AssetsManager::getInstance();
    sf::Vector2u size = asset->getAssetSprite(sptName)->getTexture()->getSize();
    lua_newtable(l);
    lua_pushinteger(l,size.x);
    lua_setfield(l,-2,"x");
    lua_pushinteger(l,size.y);
    lua_setfield(l,-2,"y");
    return 1;
}






NOT_WARNING static int musicLoad(lua_State *l){
    int n = 0;
    int need = 2;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao loadAssetMusic usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string musicName = lua_tostring(l,1);
    std::string fileName = lua_tostring(l,2);
    AssetsManager *asset = AssetsManager::getInstance();
    asset->loadAssetMusic(musicName,fileName);
    return 0;
}


NOT_WARNING static int musicPlay(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao playMusic usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string musicName = lua_tostring(l,1);
    AssetsManager *asset = AssetsManager::getInstance();
    asset->getAssetMusic(musicName)->play();
    return 0;
}


NOT_WARNING static int musicPause(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao pauseMusic usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string musicName = lua_tostring(l,1);
    AssetsManager *asset = AssetsManager::getInstance();
    asset->getAssetMusic(musicName)->pause();
    return 0;
}


NOT_WARNING static int musicStop(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao stopMusic usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string musicName = lua_tostring(l,1);
    AssetsManager *asset = AssetsManager::getInstance();
    asset->getAssetMusic(musicName)->stop();
    return 0;
}


NOT_WARNING static int isPlayingMusic(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao isPlayingMusic usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string musicName = lua_tostring(l,1);
    AssetsManager *asset = AssetsManager::getInstance();
    if ( asset->getAssetMusic(musicName)->getStatus() == sf::SoundSource::Playing )
        lua_pushboolean(l,true);
    else
        lua_pushboolean(l,false);
    return 1;
}

// retorna a duracao da musica em segundos
NOT_WARNING static int musicGetDuration(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao musicGetDuration usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string musicName = lua_tostring(l,1);
    AssetsManager *asset = AssetsManager::getInstance();
    sf::Time duration = asset->getAssetMusic(musicName)->getDuration();
    lua_pushnumber(l,duration.asSeconds());
    return 1;
}


NOT_WARNING static int musicGetVolume(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao musicGetVolume usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string musicName = lua_tostring(l,1);
    AssetsManager *asset = AssetsManager::getInstance();
    float volume = asset->getAssetMusic(musicName)->getVolume();
    lua_pushnumber(l,volume);
    return 1;
}

NOT_WARNING static int musicSetVolume(lua_State *l){
    int n = 0;
    int need = 2;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao musicSetVolume usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string musicName = lua_tostring(l,1);
    float volume = lua_tonumber(l,2);
    AssetsManager *asset = AssetsManager::getInstance();
    asset->getAssetMusic(musicName)->setVolume(volume);
    return 0;
}


// set a posicao da musica em segundos
NOT_WARNING static int musicSetPlayingOffset(lua_State *l){
    int n = 0;
    int need = 2;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao musicSetPlayingOffset usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string musicName = lua_tostring(l,1);
    float offSet = lua_tonumber(l,2);
    AssetsManager *asset = AssetsManager::getInstance();
    asset->getAssetMusic(musicName)->setPlayingOffset(sf::Time(sf::seconds(offSet)));
    return 0;
}


// consegue a posica da musica em segundos
NOT_WARNING static int musicGetPlayingOffset(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao musicGetPlayingOffset usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    std::string musicName = lua_tostring(l,1);
    AssetsManager *asset = AssetsManager::getInstance();
    float pos = asset->getAssetMusic(musicName)->getPlayingOffset().asSeconds();
    lua_pushnumber(l,pos);
    return 1;
}



NOT_WARNING static int getMouseGlobalPosition(lua_State *l){
    int n = 0;
    int need = 0;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao getMouseGlobalPosition usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    sf::Vector2i pos  = sf::Mouse::getPosition();
    lua_newtable(l);
    lua_pushinteger(l,pos.x);
    lua_setfield(l,-2,"x");
    lua_pushinteger(l,pos.y);
    lua_setfield(l,-2,"y");
    return 1;
}


NOT_WARNING static int getMouseLocalPosition(lua_State *l){
    int n = 0;
    int need = 0;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao getMouseLocalPosition usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
        return 0;
    }
    renderWindow * mRenderWindow = renderWindow::getInstance();
    sf::Vector2i pos  = sf::Mouse::getPosition( *(mRenderWindow->getRenderWindow()) );
    lua_newtable(l);
    lua_pushinteger(l,pos.x);
    lua_setfield(l,-2,"x");
    lua_pushinteger(l,pos.y);
    lua_setfield(l,-2,"y");
    return 1;
}


NOT_WARNING static int getWindowInfo(lua_State *l){
    int n = 0;
    int need = 0;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao getWindowSize usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    renderWindow *mRenderWindow = renderWindow::getInstance();
    windowInformation infos = mRenderWindow->getWindowInformation();
    lua_newtable(l);
    lua_pushinteger(l,infos.width);
    lua_setfield(l,-2,"width");
    lua_pushinteger(l,infos.height);
    lua_setfield(l,-2,"height");
    lua_pushinteger(l,infos.bitsPerPixel);
    lua_setfield(l,-2,"bitsPerPixel");
    lua_pushinteger(l,infos.fullScreen);
    lua_setfield(l,-2,"fullScreen");
    return 1;
}


NOT_WARNING static int cameraSet(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n = lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao cameraSet usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
     std::string cameraName = lua_tostring(l,1);
     renderWindow *mRenderWindow = renderWindow::getInstance();
     mRenderWindow->setCamera(cameraName);
     return 0;
}


NOT_WARNING static int cameraMove(lua_State *l){
    int n = 0;
    int need = 3;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao cameraMove usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string cameraName = lua_tostring(l,1);
    float x = lua_tonumber(l,2);
    float y = lua_tonumber(l,3);
    renderWindow *mRenderWindow = renderWindow::getInstance();

    if ( cameraName == "default")
        mRenderWindow->getDefaultCamera()->move(x,y);
    else
        mRenderWindow->getCamera(cameraName)->move(x,y);

    return 0;
}



NOT_WARNING static int cameraCreate(lua_State *l){
    int n = 0;
    int need = 2;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao createCamera usa "+ Converter::int_to_str(need) +" ( +4 opicionais) argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string cameraName = lua_tostring(l,1);
    std::string cameraTipo = lua_tostring(l,2);

    renderWindow *mRenderWindow = renderWindow::getInstance();

    if (  cameraTipo == "default"){
        mRenderWindow->createCamera(cameraName,*mRenderWindow->getDefaultCamera());
    }else{
        float w = lua_tonumber(l,3);
        float h = lua_tonumber(l,4);
        float t = lua_tonumber(l,5);
        float left = lua_tonumber(l,6);
        mRenderWindow->createCamera(cameraName,sf::FloatRect(left,t,w, h));
    }
    return 0;
}


NOT_WARNING static int cameraSetRotation(lua_State *l){
    int n = 0;
    int need = 2;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao cameraSetRotation usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string cameraName = lua_tostring(l,1);

    float angle = lua_tonumber(l,2);

    renderWindow *mRenderWindow = renderWindow::getInstance();
    mRenderWindow->getCamera(cameraName)->setRotation(angle);

    return 0;
}


NOT_WARNING static int cameraZoom(lua_State *l){
    int n = 0;
    int need = 2;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao cameraZoom usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string cameraName = lua_tostring(l,1);

    float factor = lua_tonumber(l,2);

    renderWindow *mRenderWindow = renderWindow::getInstance();
    mRenderWindow->getCamera(cameraName)->zoom(factor);

    return 0;
}



NOT_WARNING static int cameraRotate(lua_State *l){
    int n = 0;
    int need = 2;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao cameraRotate usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string cameraName = lua_tostring(l,1);

    float angle = lua_tonumber(l,2);

    renderWindow *mRenderWindow = renderWindow::getInstance();
    mRenderWindow->getCamera(cameraName)->rotate(angle);

    return 0;
}


NOT_WARNING static int cameraReset(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao cameraReset usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string cameraName = lua_tostring(l,1);

    renderWindow *mRenderWindow = renderWindow::getInstance();
    mRenderWindow->getCamera(cameraName)->reset(sf::FloatRect(0,0,mRenderWindow->getWindowInformation().width,mRenderWindow->getWindowInformation().height));
    return 0;
}


NOT_WARNING static int cameraSetDefault(lua_State *l){
    int n = 0;
    int need = 0;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao cameraSetDefault usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }

    renderWindow *mRenderWindow = renderWindow::getInstance();
    mRenderWindow->setCamera(*mRenderWindow->getDefaultCamera());
    return 0;
}



NOT_WARNING static int cameraGetRotation(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao cameraGetRotation usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string cameraName = lua_tostring(l,1);


    renderWindow *mRenderWindow = renderWindow::getInstance();
    float angle = mRenderWindow->getCamera(cameraName)->getRotation();
    lua_pushnumber(l,angle);
    return 1;
}


NOT_WARNING static int cameraGetPosition(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao cameraGetPosition usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string cameraName = lua_tostring(l,1);
    renderWindow *mRenderWindow = renderWindow::getInstance();
    sf::Vector2f view = mRenderWindow->getCamera(cameraName)->getCenter();
    lua_newtable(l);
    lua_pushnumber(l,view.x);
    lua_setfield(l,-2,"x");
    lua_pushnumber(l,view.y);
    lua_setfield(l,-2,"y");
    return 1;
}



NOT_WARNING static int rectangleCreate(lua_State *l){
    int n = 0;
    int need = 3;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao createRectangleShape usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    float w = lua_tonumber(l,2);
    float h = lua_tonumber(l,3);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->loadAssetRectangle(rectangleName,w,h);
    return 0;
}

NOT_WARNING static int rectangleSetPosition(lua_State *l){
    int n = 0;
    int need = 3;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleSetPosition usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    float x = lua_tonumber(l,2);
    float y = lua_tonumber(l,3);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getAssetRectangle(rectangleName)->setPosition(x,y);
    return 0;
}


NOT_WARNING static int rectangleSetFillColor(lua_State *l){
    int n = 0;
    int need = 4;
    if  ( ( n =lua_gettop(l)) < need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleSetFillColor usa "+ Converter::int_to_str(need) +" (+1 para alpha) argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    int r = lua_tointeger(l,2);
    int g = lua_tointeger(l,3);
    int b = lua_tointeger(l,4);
    int a = 255;
    if ( lua_gettop(l) == 5 )
        a = lua_tointeger(l,5);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getAssetRectangle(rectangleName)->setFillColor(sf::Color(r,g,b,a));
    return 0;
}


NOT_WARNING static int rectangleDraw(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleDraw usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);

    AssetsManager *assets = AssetsManager::getInstance();
    renderWindow *mWindow  = renderWindow::getInstance();
    mWindow->draw(*assets->getAssetRectangle(rectangleName));
    return 0;
}


NOT_WARNING static int rectangleSetOutlineColor(lua_State *l){
    int n = 0;
    int need = 4;
    if  ( ( n =lua_gettop(l)) < need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleSetOutlineColor usa "+ Converter::int_to_str(need) +" (+1 para alpha) argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    int r = lua_tointeger(l,2);
    int g = lua_tointeger(l,3);
    int b = lua_tointeger(l,4);
    int a = 255;
    if ( lua_gettop(l) == 5 )
        a = lua_tointeger(l,5);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getAssetRectangle(rectangleName)->setOutlineColor(sf::Color(r,g,b,a));
    return 0;
}


NOT_WARNING static int rectangleSetOutlineThickness(lua_State *l){
    int n = 0;
    int need = 2;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleSetOutlineThickness usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    float factor = lua_tonumber(l,2);

    AssetsManager *assets = AssetsManager::getInstance();
    assets->getAssetRectangle(rectangleName)->setOutlineThickness(factor);
    return 0;
}


NOT_WARNING static int rectangleSetOrigin(lua_State *l){
    int n = 0;
    int need = 3;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleSetOrigin usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    float x = lua_tonumber(l,2);
    float y = lua_tonumber(l,3);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getAssetRectangle(rectangleName)->setOrigin(sf::Vector2f(x,y));
    return 0;
}

NOT_WARNING static int rectangleSetRotation(lua_State *l){
    int n = 0;
    int need = 2;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleSetRotation usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    float angle = lua_tonumber(l,2);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getAssetRectangle(rectangleName)->setRotation(angle);
    return 0;
}


NOT_WARNING static int rectangleSetScale(lua_State *l){
    int n = 0;
    int need = 3;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleSetScale usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    float x = lua_tonumber(l,2);
    float y = lua_tonumber(l,3);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getAssetRectangle(rectangleName)->setScale(sf::Vector2f(x,y));
    return 0;
}

NOT_WARNING static int rectangleSetSize(lua_State *l){
    int n = 0;
    int need = 3;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleSetSize usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    float w = lua_tonumber(l,2);
    float h = lua_tonumber(l,3);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getAssetRectangle(rectangleName)->setSize(sf::Vector2f(w,h));
    return 0;
}



NOT_WARNING static int rectangleSetTexture(lua_State *l){
    int n = 0;
    int need = 2;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleSetTexture usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    std::string textureName = lua_tostring(l,2);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getAssetRectangle(rectangleName)->setTexture(assets->loadAssetTexture(rectangleName,textureName));
    return 0;
}



NOT_WARNING static int rectangleGetPosition(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleGetPosition usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::Vector2f pos  = assets->getAssetRectangle(rectangleName)->getPosition();
    lua_newtable(l);
    lua_pushnumber(l,pos.x);
    lua_setfield(l,-2,"x");
    lua_pushnumber(l,pos.y);
    lua_setfield(l,-2,"y");
    return 1;
}


NOT_WARNING static int rectangleGetFillColor(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleGetFillColor usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::Color c  = assets->getAssetRectangle(rectangleName)->getFillColor();
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


NOT_WARNING static int rectangleGetOutlineColor(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleGetOutlineColor usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::Color c  = assets->getAssetRectangle(rectangleName)->getOutlineColor();
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



NOT_WARNING static int rectangleGetOutlineThickness(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleGetOutlineThickness usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    float thickness = assets->getAssetRectangle(rectangleName)->getOutlineThickness();
    lua_pushnumber(l,thickness);
    return 1;
}

NOT_WARNING static int rectangleGetGlobalBounds(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleGetGlobalBounds usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::FloatRect globalBounds = assets->getAssetRectangle(rectangleName)->getGlobalBounds();

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


NOT_WARNING static int rectangleGetLocalBounds(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleGetLocalBounds usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::FloatRect localBounds = assets->getAssetRectangle(rectangleName)->getLocalBounds();

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



NOT_WARNING static int rectangleGetOrigin(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleGetOrigin usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::Vector2f origin = assets->getAssetRectangle(rectangleName)->getOrigin();
    lua_newtable(l);
    lua_pushnumber(l,origin.x);
    lua_setfield(l,-2,"x");
    lua_pushnumber(l,origin.y);
    lua_setfield(l,-2,"y");
    return 1;
}


NOT_WARNING static int rectangleGetRotation(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleGetRotation usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    float angle = assets->getAssetRectangle(rectangleName)->getRotation();
    lua_pushnumber(l,angle);
    return 1;
}

NOT_WARNING static int rectangleGetScale(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleScale usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::Vector2f scale = assets->getAssetRectangle(rectangleName)->getScale();
    lua_newtable(l);
    lua_pushnumber(l,scale.x);
    lua_setfield(l,-2,"x");
    lua_pushnumber(l,scale.y);
    lua_setfield(l,-2,"y");
    return 1;
}


NOT_WARNING static int rectangleGetSize(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleSize usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    AssetsManager *assets = AssetsManager::getInstance();
    sf::Vector2f size = assets->getAssetRectangle(rectangleName)->getSize();
    lua_newtable(l);
    lua_pushnumber(l,size.x);
    lua_setfield(l,-2,"x");
    lua_pushnumber(l,size.y);
    lua_setfield(l,-2,"y");
    return 1;
}



NOT_WARNING static int rectangleMove(lua_State *l){
    int n = 0;
    int need = 3;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleMove usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    float x = lua_tonumber(l,2);
    float y = lua_tonumber(l,3);

    AssetsManager *assets = AssetsManager::getInstance();
    assets->getAssetRectangle(rectangleName)->move(sf::Vector2f(x,y));
    return 0;
}


NOT_WARNING static int rectangleRotate(lua_State *l){
    int n = 0;
    int need = 2;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleRotate usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    float angle = lua_tonumber(l,2);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getAssetRectangle(rectangleName)->rotate(angle);
    return 0;
}

NOT_WARNING static int rectangleScale(lua_State *l){
    int n = 0;
    int need = 3;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao rectangleScale usa "+ Converter::int_to_str(need) +"  argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    std::string rectangleName = lua_tostring(l,1);
    float x = lua_tonumber(l,2);
    float y = lua_tonumber(l,2);
    AssetsManager *assets = AssetsManager::getInstance();
    assets->getAssetRectangle(rectangleName)->scale(sf::Vector2f(x,y));
    return 0;
}













NOT_WARNING static int isKeyPress(lua_State *l){
    int n = 0;
    int need = 1;
    if  ( ( n =lua_gettop(l)) != need){
        Debugger *dbg = Debugger::getInstance();
        dbg->log(WARNING,1,("A funcao isKeyPress usa "+ Converter::int_to_str(need) +" argumento [" + Converter::int_to_str(n)+"] argumentos passados.").c_str());
    }
    Key key;

    if ( ! lua_isnumber(l,1) ){
        key = Converter::str_to_key(lua_tostring(l,1));

    }else{
        key = (Key)lua_tointeger(l,1);
    }

    if (  sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key) )
        lua_pushboolean(l,true);
    else
        lua_pushboolean(l,false);

    return 1;
}





void registerAllLuaFunctions();



#endif // LUAFUNCTIONS_H
