#include "Shape.h"

using namespace ME;

Shape::Shape(const Vect2f &size, const Color &color, const Vect2f &pos) {
    mType = "shape";
    setSize(size);
    setColor(color);
    setPosition(pos);
}

void Shape::draw(sf::RenderWindow *renderWindow) {
    renderWindow->draw(mShape);
}

void Shape::setPosition(const Vect2f &pos) {
    mShape.setPosition(sf::Vector2f(pos.x, pos.y));
}

Vect2f Shape::getPosition() {
    return Vect2f(mShape.getPosition().x, mShape.getPosition().y);
}

void Shape::move(const Vect2f &pos) {
    mShape.move(sf::Vector2f(pos.x, pos.y));
}

void Shape::setSize(const Vect2f &size) {
    mShape.setSize(sf::Vector2f(size.x, size.y));
}

Vect2f Shape::getSize() {
    return Vect2f(mShape.getSize().x, mShape.getSize().y);
}

Vect2f Shape::getScale() {
    return Vect2f(mShape.getScale().x, mShape.getScale().y);
}

void Shape::setScale(const Vect2f &scale) {
    mShape.setScale(sf::Vector2f(scale.x, scale.y));
}

void Shape::setColor(const Color &color) {
    mShape.setFillColor(sf::Color(color.red, color.green, color.blue, color.alpha));
}

Color Shape::getColor() {
    return Color(mShape.getFillColor().r, mShape.getFillColor().g, mShape.getFillColor().b, mShape.getFillColor().a);
}

void Shape::setBorderColor(const Color &color) {
    mShape.setOutlineColor(sf::Color(color.red, color.green, color.blue, color.alpha));
}

Color Shape::getBorderColor() {
    return Color(mShape.getOutlineColor().r, mShape.getOutlineColor().g, mShape.getOutlineColor().b, mShape.getOutlineColor().a);
}

void Shape::setBorderSize(const float& size) {
    mShape.setOutlineThickness(size);
}

float Shape::getBorderSize() {
    return mShape.getOutlineThickness();
}

float Shape::getRotation() {
    return mShape.getRotation();
}

void Shape::setRotation(const float &angle) {
    mShape.setRotation(angle);
}

void Shape::rotate(const float &angle) {
    mShape.rotate(angle);
}

Vect2f Shape::getOrigin() {
    return Vect2f(mShape.getOrigin().x, mShape.getOrigin().y);
}

void Shape::setOrigin(const Vect2f &origin) {
    mShape.setOrigin(origin.x, origin.y);
}

Area Shape::getLocalBounds() {
    return Area(mShape.getLocalBounds().left, mShape.getLocalBounds().top, mShape.getLocalBounds().width, mShape.getLocalBounds().height);
}

Area Shape::getGlobalBounds() {
    return Area(mShape.getGlobalBounds().left, mShape.getGlobalBounds().top, mShape.getGlobalBounds().width, mShape.getGlobalBounds().height);
}
