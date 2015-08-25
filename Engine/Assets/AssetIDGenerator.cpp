#include "AssetIDGenerator.h"

using namespace ME;

AssetID AssetIDGenerator::id = 0;

AssetID AssetIDGenerator::get() {
    return id++;
}

AssetIDGenerator::AssetIDGenerator() {

}

