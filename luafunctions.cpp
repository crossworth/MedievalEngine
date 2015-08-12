#include "luafunctions.h"

void registerFunctions() {

    // Global
    mLua->registerFunction("log", log); //ok
    mLua->registerFunction("getWindowInfo", getWindowInfo); // ok
    mLua->registerFunction("changeGameState", changeGameState);
    mLua->registerFunction("setState", setState); // ok
    mLua->registerFunction("getState", getState); // ok
    mLua->registerFunction("getTimer", getTimer); // ok
    mLua->registerFunction("resetTimer", resetTimer); // ok
    mLua->registerFunction("registerCallBack", registerCallBack); // ok

    // Effects
    mLua->registerFunction("fadeIn", fadeIn); // ok
    mLua->registerFunction("fadeOut", fadeOut); // ok

    //Events
    mLua->registerFunction("getMouseGlobalPosition", getMouseGlobalPosition); // ok
    mLua->registerFunction("getMouseLocalPosition", getMouseLocalPosition); // ok
    mLua->registerFunction("isKeyPressed", isKeyPressed); // ok

    //Camera
    mLua->registerFunction("cameraMove", cameraMove);
    mLua->registerFunction("cameraSet", cameraSet);
    mLua->registerFunction("cameraCreate", cameraCreate);
    mLua->registerFunction("cameraSetRotation", cameraSetRotation);
    mLua->registerFunction("cameraZoom", cameraZoom);
    mLua->registerFunction("cameraRotate", cameraRotate);
    mLua->registerFunction("cameraGetRotation", cameraGetRotation);
    mLua->registerFunction("cameraGetPosition", cameraGetPosition);
    mLua->registerFunction("cameraReset", cameraReset);
    mLua->registerFunction("cameraSetDefault", cameraSetDefault);

    //RectangleShape
    mLua->registerFunction("rectangleCreate", rectangleCreate); // ok
    mLua->registerFunction("rectangleSetPosition", rectangleSetPosition); // ok
    mLua->registerFunction("rectangleSetFillColor", rectangleSetFillColor); // ok
    mLua->registerFunction("rectangleDraw", rectangleDraw); // ok
    mLua->registerFunction("rectangleSetOutlineColor", rectangleSetOutlineColor); // ok
    mLua->registerFunction("rectangleSetOutlineThickness", rectangleSetOutlineThickness); // ok
    mLua->registerFunction("rectangleSetOrigin", rectangleSetOrigin); // ok
    mLua->registerFunction("rectangleSetRotation", rectangleSetRotation); // ok
    mLua->registerFunction("rectangleSetScale", rectangleSetScale); // ok
    mLua->registerFunction("rectangleSetSize", rectangleSetSize); // ok
    mLua->registerFunction("rectangleSetTexture", rectangleSetTexture); // ok
    mLua->registerFunction("rectangleGetPosition", rectangleGetPosition); // ok
    mLua->registerFunction("rectangleGetFillColor", rectangleGetFillColor); // ok
    mLua->registerFunction("rectangleGetOutlineColor", rectangleGetOutlineColor); // ok
    mLua->registerFunction("rectangleGetOutlineThickness", rectangleGetOutlineThickness); // ok
    mLua->registerFunction("rectangleGetGlobalBounds", rectangleGetGlobalBounds); // ok
    mLua->registerFunction("rectangleGetLocalBounds", rectangleGetLocalBounds); // ok
    mLua->registerFunction("rectangleGetOrigin", rectangleGetOrigin); // ok
    mLua->registerFunction("rectangleGetRotation", rectangleGetRotation); // ok
    mLua->registerFunction("rectangleGetScale", rectangleGetScale); //  ok
    mLua->registerFunction("rectangleGetSize", rectangleGetSize); // ok
    mLua->registerFunction("rectangleMove", rectangleMove); // ok
    mLua->registerFunction("rectangleScale", rectangleScale); // ok
    mLua->registerFunction("rectangleRotate", rectangleRotate); // ok

    // Sprite
    mLua->registerFunction("spriteCreate", spriteCreate); // ok
    mLua->registerFunction("spriteSetTexture", spriteSetTexture);
    mLua->registerFunction("spriteDraw", spriteDraw); // ok
    mLua->registerFunction("spriteRotate", spriteRotate);
    mLua->registerFunction("spriteGetRotation", spriteGetRotation);
    mLua->registerFunction("spriteMove", spriteMove);
    mLua->registerFunction("spriteSetPosition", spriteSetPosition);
    mLua->registerFunction("spriteGetPosition", spriteGetPosition);
    mLua->registerFunction("spriteSetScale", spriteSetScale);
    mLua->registerFunction("spriteScale", spriteScale);
    mLua->registerFunction("spriteSetOrigin", spriteSetOrigin);
    mLua->registerFunction("spriteGetOrigin", spriteGetOrigin);
    mLua->registerFunction("spriteSetColor", spriteSetColor);
    mLua->registerFunction("spriteGetColor", spriteGetColor);
    mLua->registerFunction("spriteGetGlobalBounds", spriteGetGlobalBounds);
    mLua->registerFunction("spriteGetLocalBounds", spriteGetLocalBounds);
    mLua->registerFunction("spriteGetSize", spriteGetSize);
    mLua->registerFunction("spriteGetScale", spriteGetScale);
    mLua->registerFunction("spriteSetRect", spriteSetRect);

    // Texture
    mLua->registerFunction("textureCreate", textureCreate); // ok

    // Music
    mLua->registerFunction("musicLoad", musicLoad); // ok
    mLua->registerFunction("musicPlay", musicPlay); // ok
    mLua->registerFunction("musicPause",musicPause); // ok
    mLua->registerFunction("musicStop", musicStop); // ok
    mLua->registerFunction("isPlayingMusic", isPlayingMusic); // ok
    mLua->registerFunction("musicGetDuration", musicGetDuration); // ok
    mLua->registerFunction("musicGetVolume", musicGetVolume); // ok
    mLua->registerFunction("musicSetVolume", musicSetVolume); // ok
    mLua->registerFunction("musicGetPlayingOffset", musicGetPlayingOffset); // ok
    mLua->registerFunction("musicSetPlayingOffset", musicSetPlayingOffset); // ok


    Debugger *dbg = Debugger::getInstance();
    dbg->log(VERBOSE, 1,"[registerFunctions] Lua functions registered");
}
