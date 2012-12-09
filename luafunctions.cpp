#include "luafunctions.h"



void registerAllLuaFunctions(){
    // Global
    mLua->registerFunction("log",log);
    mLua->registerFunction("getWindowInfo",getWindowInfo);

    //Events
    mLua->registerFunction("getMouseGlobalPosition",getMouseGlobalPosition);
    mLua->registerFunction("getMouseLocalPosition",getMouseLocalPosition);
    mLua->registerFunction("isKeyPress",isKeyPress);


    //Camera
    mLua->registerFunction("cameraMove",cameraMove);
    mLua->registerFunction("cameraSet",cameraSet);
    mLua->registerFunction("cameraCreate",cameraCreate);
    mLua->registerFunction("cameraSetRotation",cameraSetRotation);
    mLua->registerFunction("cameraZoom",cameraZoom);
    mLua->registerFunction("cameraRotate",cameraRotate);
    mLua->registerFunction("cameraGetRotation",cameraGetRotation);
    mLua->registerFunction("cameraGetPosition",cameraGetPosition);
    mLua->registerFunction("cameraReset",cameraReset);
    mLua->registerFunction("cameraSetDefault",cameraSetDefault);


    //RectangleShape
    mLua->registerFunction("rectangleCreate",rectangleCreate);
    mLua->registerFunction("rectangleSetPosition",rectangleSetPosition);
    mLua->registerFunction("rectangleSetFillColor",rectangleSetFillColor);
    mLua->registerFunction("rectangleDraw",rectangleDraw);
    mLua->registerFunction("rectangleSetOutlineColor",rectangleSetOutlineColor);
    mLua->registerFunction("rectangleSetOutlineThickness",rectangleSetOutlineThickness);
    mLua->registerFunction("rectangleSetOrigin",rectangleSetOrigin);
    mLua->registerFunction("rectangleSetRotation",rectangleSetRotation);
    mLua->registerFunction("rectangleSetScale",rectangleSetScale);
    mLua->registerFunction("rectangleSetSize",rectangleSetSize);
    mLua->registerFunction("rectangleSetTexture",rectangleSetTexture);
    mLua->registerFunction("rectangleGetPosition",rectangleGetPosition);
    mLua->registerFunction("rectangleGetFillColor",rectangleGetFillColor);
    mLua->registerFunction("rectangleGetOutlineColor",rectangleGetOutlineColor);
    mLua->registerFunction("rectangleGetOutlineThickness",rectangleGetOutlineThickness);
    mLua->registerFunction("rectangleGetGlobalBounds",rectangleGetGlobalBounds);
    mLua->registerFunction("rectangleGetLocalBounds",rectangleGetLocalBounds);
    mLua->registerFunction("rectangleGetOrigin",rectangleGetOrigin);
    mLua->registerFunction("rectangleGetRotation",rectangleGetRotation);
    mLua->registerFunction("rectangleGetScale",rectangleGetScale);
    mLua->registerFunction("rectangleGetSize",rectangleGetSize);
    mLua->registerFunction("rectangleMove",rectangleMove);
    mLua->registerFunction("rectangleScale",rectangleScale);
    mLua->registerFunction("rectangleRotate",rectangleRotate);





    // Sprite
    mLua->registerFunction("spriteLoad",spriteLoad);
    mLua->registerFunction("spriteLoadFromTexture",spriteLoadFromTexture);
    mLua->registerFunction("spriteDraw",spriteDraw);
    mLua->registerFunction("spriteRotate",spriteRotate);
    mLua->registerFunction("spriteGetRotate",spriteGetRotate);
    mLua->registerFunction("spriteMove",spriteMove);
    mLua->registerFunction("spriteSetPosition",spriteSetPosition);
    mLua->registerFunction("spriteGetPosition",spriteGetPosition);
    mLua->registerFunction("spriteSetScale",spriteSetScale);
    mLua->registerFunction("spriteScale",spriteScale);
    mLua->registerFunction("spriteSetOrigin",spriteSetOrigin);
    mLua->registerFunction("spriteGetOrigin",spriteGetOrigin);
    mLua->registerFunction("spriteSetColor",spriteSetColor);
    mLua->registerFunction("spriteGetColor",spriteGetColor);
    mLua->registerFunction("spriteGetGlobalBounds",spriteGetGlobalBounds);
    mLua->registerFunction("spriteGetLocalBounds",spriteGetLocalBounds);
    mLua->registerFunction("spriteGetSize",spriteGetSize);
    mLua->registerFunction("spriteGetScale",spriteGetScale);


    // Music
    mLua->registerFunction("musicLoad",musicLoad);
    mLua->registerFunction("musicPlay",musicPlay);
    mLua->registerFunction("musicPause",musicPause);
    mLua->registerFunction("musicStop",musicStop);
    mLua->registerFunction("isPlayingMusic",isPlayingMusic);
    mLua->registerFunction("musicGetDuration",musicGetDuration);
    mLua->registerFunction("musicGetVolume",musicGetVolume);
    mLua->registerFunction("musicSetVolume",musicSetVolume);
    mLua->registerFunction("musicGetPlayingOffset",musicGetPlayingOffset);
    mLua->registerFunction("musicSetPlayingOffset",musicSetPlayingOffset);


}
