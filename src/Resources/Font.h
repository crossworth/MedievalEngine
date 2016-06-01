#ifndef FONT_H
#define FONT_H
#include <SFML/Graphics.hpp>
#include "LogInc.h"
#include "Resources/Resource.h"
#include "Resources/ResourceIDGenerator.h"


namespace ME {

class Font : public Resource {
public:
    Font();
    bool loadFromFile(const std::string& fileName);
    bool loadFromMemory(MEByte* bytes, std::size_t size);
    sf::Font* getResourcePointer();

    int getLineSpacing(const unsigned int& size);

    /**
     * Default font - fallback font
     */
    static ResourceID DEFAULT_FONT;
private:
    sf::Font mFont;
};

}

#endif // FONT_H
