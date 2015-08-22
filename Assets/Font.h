#ifndef FONT_H
#define FONT_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <LogInc.h>
#include <Helper/ID.h>
#include <Helper/Types.h>
#include <Assets/Asset.h>


namespace ME {

class Font : public Asset {
public:
    Font();
    Font(const std::string& fileName);
    sf::Font* loadFromFile(const std::string& fileName);
    sf::Font* loadFromMemory(SM::BYTE* bytes, std::size_t size);
    sf::Font* getResourcePointer();
    static MEid DEFAULT_FONT;
private:
    sf::Font mFont;
};

}

#endif // FONT_H
