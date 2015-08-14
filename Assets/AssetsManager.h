#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H
#include <Headers.h>

namespace ME {

class AssetsManager {
public:
    static AssetsManager* getInstance();
    ~AssetsManager();

    MEid loadTexture(const std::string &fileName);

    Asset* getID(MEid);

private:
    static AssetsManager* mInstance;
    std::map<MEid, Asset*> mAssets;

    AssetsManager();
};

}

#endif // ASSETSMANAGER_H
