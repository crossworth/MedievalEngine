#include "Mouse.h"

using namespace ME;

bool Mouse::isButtonPressed(Mouse::Button button) {
    return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
}

Vect2i Mouse::getPosition() {
    return Vect2i(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
}

Vect2i Mouse::getPosition(sf::Window& window) {
    return Vect2i(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}

void Mouse::setPosition(const Vect2i &position) {
    sf::Mouse::setPosition(sf::Vector2i(position.x, position.y));
}
