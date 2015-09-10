#ifndef RESOURCEIDGENERATOR_H
#define RESOURCEIDGENERATOR_H
#include "Helper/Types.h"


namespace ME {

// NOTE(Pedro): This is thread safe
// since we initialize the member during the static initialization
class ResourceIDGenerator {
public:
    static ResourceID get();
private:
    static ResourceID id;
    ResourceIDGenerator();
};

}

#endif // RESOURCEIDGENERATOR_H
