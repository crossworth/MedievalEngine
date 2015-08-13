#ifndef ASSET_H
#define ASSET_H
#include <iostream>

namespace ME {

class Asset {
public:
    Asset();

    std::string getType();

private:
    std::string mType;
};

}

#endif // ASSET_H
