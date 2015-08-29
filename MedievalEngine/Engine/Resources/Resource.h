#ifndef ASSET_H
#define ASSET_H
#include <iostream>


namespace ME {

class Resource {
public:
    enum Type {FONT, MUSIC, SHAPE, SOUND, SPRITE, SPRITEANIMATION, TEXT, TEXTURE};
public:
    Resource();
    virtual ~Resource();
    Type getType();
protected:
    Type m_type;
};

}

#endif // ASSET_H
