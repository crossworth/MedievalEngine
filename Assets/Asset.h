#ifndef ASSET_H
#define ASSET_H
#include <iostream>


namespace ME {

class Asset {
public:
    Asset();
    virtual ~Asset();
    std::string getType();
protected:
    std::string mType;
};

}

#endif // ASSET_H
