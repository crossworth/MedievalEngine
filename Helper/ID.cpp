#include "ID.h"

using namespace ME;

MEid ID::id = 0;

MEid ID::get() {
    return id++;
}

ID::ID() {

}

