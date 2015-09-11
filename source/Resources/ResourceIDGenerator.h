#ifndef RESOURCEIDGENERATOR_H
#define RESOURCEIDGENERATOR_H
#include <atomic>
#include "Helper/Types.h"


namespace ME {

// NOTE(Pedro): This is thread safe
// since we initialize the member during the static initialization
// ANDDDDD we're using atomic data
class ResourceIDGenerator {
public:
    static ResourceID get();
private:
    static std::atomic<ResourceID> id;
};

}

#endif // RESOURCEIDGENERATOR_H
