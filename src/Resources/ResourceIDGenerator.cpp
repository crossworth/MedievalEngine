#include "ResourceIDGenerator.h"

using namespace ME;

std::atomic<ResourceID> ResourceIDGenerator::id = {0};

ResourceID ResourceIDGenerator::get() {
    return id++;
}


