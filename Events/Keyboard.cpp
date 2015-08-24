#include "Keyboard.h"

using namespace ME;

bool Keyboard::isKeyPressed(Keyboard::KEY key) {
    return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
}
