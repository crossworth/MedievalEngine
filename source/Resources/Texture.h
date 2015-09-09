#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "LogInc.h"
#include "Resources/Resource.h"


namespace ME {

class Texture : public Resource {
public:
    // TODO(Pedro): Remove the constructor that can fail
    Texture(const std::string& fileName);
    sf::Texture* loadFromFile(const std::string& fileName);
    sf::Texture* getResourcePointer();
private:
    sf::Texture mTexture;
};

}

#endif // TEXTURE_H
