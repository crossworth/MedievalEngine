#ifndef ID_H
#define ID_H


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

#endif // ID_H
