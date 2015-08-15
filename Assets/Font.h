#ifndef FONT_H
#define FONT_H
#include <SFML/Graphics.hpp>
#include <Assets/Asset.h>
#include <LogInc.h>
#include <iostream>

namespace ME {

class Font : public Asset {
public:
    Font(const std::string &fileName);
    sf::Font* loadFromFile(const std::string &fileName);
    sf::Font* getResourcePointer();
private:
    sf::Font mFont;
};

}

#endif // FONT_H
