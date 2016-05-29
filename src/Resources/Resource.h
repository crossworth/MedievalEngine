#ifndef RESOURCE_H
#define RESOURCE_H
#include <iostream>


namespace ME {

class Resource {
public:
    enum Type {
        FONT,
        MUSIC,
        SHAPE,
        SOUND,
        SPRITE,
        SPRITEANIMATION,
        TEXT,
        TEXTURE
    };
public:
    Resource();
    virtual ~Resource();
    Type getType();
    bool isValid();
protected:
    Type mType;
    bool mIsValid;
};

}

#endif // RESOURCE_H
