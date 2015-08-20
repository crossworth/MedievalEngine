#include "Shape.h"

using namespace ME;

Shape::Shape(const Vect2f &size, const Color &color, const Vect2f &pos) {
    mType = "shape";
    setSize(size);
    setColor(color);
    setPosition(pos);
    _isGradientColor = false;
}

void Shape::draw(sf::RenderWindow *renderWindow) {
    if(_isGradientColor) {
        Area mArea = getLocalBounds();

        sf::Vertex mGradientVertex[] = {
            sf::Vertex(sf::Vector2f(getPosition().x, getPosition().y), sf::Color(mGradientColor.color1.red, mGradientColor.color1.green, mGradientColor.color1.blue, mGradientColor.color1.alpha)),
            sf::Vertex(sf::Vector2f(mArea.width  + getPosition().x, getPosition().y), sf::Color(mGradientColor.color1.red, mGradientColor.color1.green, mGradientColor.color1.blue, mGradientColor.color1.alpha)),
            sf::Vertex(sf::Vector2f(mArea.width + getPosition().x, mArea.height + getPosition().y), sf::Color(mGradientColor.color2.red, mGradientColor.color2.green, mGradientColor.color2.blue, mGradientColor.color2.alpha)),
            sf::Vertex(sf::Vector2f(getPosition().x, mArea.height + getPosition().y), sf::Color(mGradientColor.color2.red, mGradientColor.color2.green, mGradientColor.color2.blue, mGradientColor.color2.alpha)),
        };

        renderWindow->draw(mGradientVertex, 4, sf::Quads);
    } else {
        renderWindow->draw(mShape);
    }
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
    _isGradientColor = false;
}

Color Shape::getColor() {
    return Color(mShape.getFillColor().r, mShape.getFillColor().g, mShape.getFillColor().b, mShape.getFillColor().a);
}

void Shape::setColor(const GradientColor &color) {
    _isGradientColor = true;
    mGradientColor = color;
}

GradientColor Shape::getColorGradient() {
    return mGradientColor;
}

bool Shape::isGradientColor() {
    return _isGradientColor;
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
