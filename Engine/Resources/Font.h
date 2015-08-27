#ifndef FONT_H
#define FONT_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "LogInc.h"
#include "Helper/Types.h"
#include "Resources/Resource.h"
#include "Resources/ResourceIDGenerator.h"


namespace ME {

class Font : public Resource {
public:
    Font();
    Font(const std::string& fileName);
    sf::Font* loadFromFile(const std::string& fileName);
    sf::Font* loadFromMemory(_BYTE* bytes, std::size_t size);
    sf::Font* getResourcePointer();
    static ResourceID DEFAULT_FONT;
private:
    sf::Font mFont;
};

}

#endif // FONT_H
