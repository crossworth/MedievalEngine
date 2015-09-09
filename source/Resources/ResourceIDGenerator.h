#ifndef RESOURCEIDGENERATOR_H
#define RESOURCEIDGENERATOR_H


namespace ME {


typedef unsigned long int ResourceID;

// TODO(Pedro): Make this thread safe
// by using std::atomic
class ResourceIDGenerator {
public:
    static ResourceID get();
private:
    static ResourceID id;
    ResourceIDGenerator();
};

}

#endif // RESOURCEIDGENERATOR_H
