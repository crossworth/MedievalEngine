#ifndef FONT_H
#define FONT_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <LogInc.h>
#include <Assets/Asset.h>


namespace ME {

class Font : public Asset {
public:
    Font(const std::string& fileName);
    sf::Font* loadFromFile(const std::string& fileName);
    sf::Font* getResourcePointer();
private:
    sf::Font mFont;
};

}

#endif // FONT_H
