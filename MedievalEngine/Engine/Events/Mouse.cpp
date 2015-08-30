#include "Mouse.h"
#include "Graphics/Window.h"



using namespace ME;

bool Mouse::isButtonPressed(Mouse::Button button) {
    return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
}

Vect2i Mouse::getPosition() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    return Vect2i(mousePosition.x, mousePosition.y);
}

Vect2i Mouse::getPosition(Window* window) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window->getWindowPtr());
    return Vect2i(mousePosition.x, mousePosition.y);
}

void Mouse::setPosition(const Vect2i& position) {
    sf::Mouse::setPosition(sf::Vector2i(position.x, position.y));
}
