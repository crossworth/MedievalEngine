#include "Resource.h"

using namespace ME;

Resource::Resource() {
	// TODO(Pedro): Do we need this flag?
	// on Text its not been updated
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
