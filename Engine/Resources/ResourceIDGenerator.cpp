#include "ResourceIDGenerator.h"

using namespace ME;

ResourceID ResourceIDGenerator::id = 0;

ResourceID ResourceIDGenerator::get() {
    return id++;
}

ResourceIDGenerator::ResourceIDGenerator() {

}

