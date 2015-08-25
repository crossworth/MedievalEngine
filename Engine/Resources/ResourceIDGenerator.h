#ifndef RESOURCEIDGENERATOR_H
#define RESOURCEIDGENERATOR_H


namespace ME {

typedef unsigned long int ResourceID;

class ResourceIDGenerator {
public:
    static ResourceID get();
private:
    static ResourceID id;
    ResourceIDGenerator();
};

}

#endif // RESOURCEIDGENERATOR_H
