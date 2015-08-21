#ifndef ID_H
#define ID_H


namespace ME {

typedef unsigned long int MEid;

class ID {
public:
    static MEid get();
private:
    static MEid id;
    ID();
};

}

#endif // ID_H
