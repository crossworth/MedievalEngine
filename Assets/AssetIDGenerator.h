#ifndef ID_H
#define ID_H


namespace ME {

typedef unsigned long int AssetID;

class AssetIDGenerator {
public:
    static AssetID get();
private:
    static AssetID id;
    AssetIDGenerator();
};

}

#endif // ID_H
