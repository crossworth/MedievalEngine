#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Assets/Asset.h>

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
