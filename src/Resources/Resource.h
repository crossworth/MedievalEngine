#ifndef MEDIEVALENGINE_RESOURCES_RESOURCE_H_
#define MEDIEVALENGINE_RESOURCES_RESOURCE_H_

namespace ME {

class Resource {
public:

    enum class Type {
        FONT,
        MUSIC,
        SHAPE,
        SOUND,
        SPRITE,
        SPRITEANIMATION,
        TEXT,
        TEXTURE
    };

    Resource();
    virtual ~Resource();
    Type getType();
    bool isValid();
protected:
    Type mType;
    bool mIsValid;
};

}

#endif // MEDIEVALENGINE_RESOURCES_RESOURCE_H_
