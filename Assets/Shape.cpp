#include "Shape.h"
#include "cmath"

using namespace ME;

Shape::Shape(const Vect2f &size, const Color &color, const Vect2f &pos) {
    mType = "shape";
    setSize(size);
    setColor(color);
    setPosition(pos);
    _isGradientColor = false;
    _radius          = 90.0f;
    _numberPoints    = 30;
}

void Shape::draw(sf::RenderWindow *renderWindow) {
    std::vector<sf::Vertex> mVertex;

    for(unsigned int i = 0; i < _numberPoints * 4; i++) {

        float deltaAngle = 90.0f/(_numberPoints-1);
        sf::Vector2f center;
        unsigned int centerIndex = i/_numberPoints;
        static const float pi = 3.141592654f;

        sf::Vector2f mySize(getSize().x, getSize().y);

        switch(centerIndex) {
            case 0: center.x = mySize.x - _radius; center.y = _radius; break;
            case 1: center.x = _radius; center.y = _radius; break;
            case 2: center.x = _radius; center.y = mySize.y - _radius; break;
            case 3: center.x = mySize.x - _radius; center.y = mySize.y - _radius; break;
        }

        sf::Vector2f pos    = mShape.getPosition();
        sf::Vector2f vecPos = sf::Vector2f(_radius*std::cos(deltaAngle*(i-centerIndex)*pi/180)+center.x + pos.x,
                                        -_radius*std::sin(deltaAngle*(i-centerIndex)*pi/180)+center.y + pos.y);

        if(_isGradientColor) {
            if (vecPos.y < mShape.getSize().y) {
                mVertex.push_back(sf::Vertex(vecPos, sf::Color(mGradientColor.color1.red, mGradientColor.color1.green, mGradientColor.color1.blue, mGradientColor.color1.alpha)));
            } else {
                mVertex.push_back(sf::Vertex(vecPos, sf::Color(mGradientColor.color1.green, mGradientColor.color2.green, mGradientColor.color2.blue, mGradientColor.color2.alpha)));
            }
        } else {
            mVertex.push_back(sf::Vertex(vecPos, mShape.getFillColor()));
        }
    }

    renderWindow->draw(&mVertex[0], mVertex.size(), sf::TrianglesFan);
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

void Shape::setColor(const ColorGradient &color) {
    _isGradientColor = true;
    mGradientColor = color;
}

ColorGradient Shape::getColorGradient() {
    return mGradientColor;
}

bool Shape::isGradientColor() {
    return _isGradientColor;
}

void Shape::setRadius(const float& radius) {
    _radius = radius;
}

float Shape::getRadius() {
    return _radius;
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
