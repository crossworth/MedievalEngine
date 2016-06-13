#ifndef MEDIEVALENGINE_RESOURCES_FONT_H_
#define MEDIEVALENGINE_RESOURCES_FONT_H_
#include <SFML/Graphics.hpp>

#include "LogInc.h"

#include "Resources/Resource.h"


namespace ME {

class Font : public Resource {
public:
    Font();
    bool loadFromFile(const std::string &fileName);
    bool loadFromMemory(byte *bytes, std::size_t size);
    sf::Font* getResourcePointer();

    float getLineSpacing(const unsigned int &size) const;
private:
    sf::Font mFont;
};

}

#endif // MEDIEVALENGINE_RESOURCES_FONT_H_
