#include "ID.h"

using namespace ME;

unsigned int ID::id = 0;

unsigned int ID::get() {
    return id++;
}

ID::ID() {

}

