#ifndef TEXTURE_H
#define TEXTURE_H
#include <Assets/Asset.h>
#include <Headers.h>


namespace ME {

class Texture : public Asset {
public:
    Texture(const std::string &fileName);
    sf::Texture* loadFromFile(const std::string &fileName);
    sf::Texture* getResourcePointer();

private:
    sf::Texture mTexture;


};

}

#endif // TEXTURE_H
