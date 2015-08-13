#ifndef ID_H
#define ID_H


namespace ME {

class ID {
public:
    static unsigned int get();
private:
    static unsigned int id;
    ID();
};

}

#endif // ID_H
