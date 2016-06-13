#include "Resource.h"

using namespace ME;

Resource::Resource() {
    mIsValid = false;
}

Resource::~Resource() {

}

bool Resource::isValid() {
    return mIsValid;
}

Resource::Type Resource::getType() {
    return mType;
}
