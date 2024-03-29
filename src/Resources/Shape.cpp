#include "Shape.h"
#include "Graphics/Window.h"
#include "cmath"

using namespace ME;

Shape::Shape(const Vect2f &size, const Color &color, const Vect2f &pos) {
    mType            = Resource::Type::SHAPE;
    mRadius          = 0.0f;
    mIsValid         = true;
    mNumberPoints    = 30;
    mIsGradientColor = false;

    setSize(size);
    setColor(color);
    setPosition(pos);
}


void Shape::draw(Window &window) {
    std::vector<sf::Vertex> vertexVector;

    sf::Vector2f shapeSize(getSize().x, getSize().y);

    // if the radius is bigger than the half of the minimum size (width or hight)
    // cause some troubles, so we reset to the best opition possible
    // Since the max radius size is 50%, which makes a circle
    // bigger than that cause undefined behaviour 
    if (mRadius > 0.0f) {
        float shapeMinSize = std::min(shapeSize.x, shapeSize.y) / 2;
        if (mRadius > shapeMinSize) {
            mRadius = shapeMinSize;
        }
    }

    uint32 numberPointsTotal = mNumberPoints * 4;
    for(uint32 i = 0; i < numberPointsTotal; i++) {
        sf::Vector2f center;

        float deltaAngle      = 90.0f / (mNumberPoints - 1);
        uint32 centerIndex    = i / mNumberPoints;

        switch(centerIndex) {
            case 0:
                center.x = shapeSize.x - mRadius;
                center.y = mRadius;
                break;
            case 1:
                center.x = mRadius;
                center.y = mRadius;
                break;
            case 2:
                center.x = mRadius;
                center.y = shapeSize.y - mRadius;
                break;
            case 3:
                center.x = shapeSize.x - mRadius;
                center.y = shapeSize.y - mRadius;
                break;
        }

        sf::Vector2f shapePos  = mShape.getPosition();

        float posX = mRadius * std::cos(deltaAngle *
                     (i - centerIndex) * Math::PI / 180) + center.x + shapePos.x;

        float posY = -mRadius * std::sin(deltaAngle *
                     (i - centerIndex) * Math::PI / 180) + center.y + shapePos.y;

        sf::Vector2f vertexPos = sf::Vector2f(posX, posY);

        if (mIsGradientColor) {
            if (posY < (mShape.getPosition().y + (mShape.getSize().y / 2))) {
                vertexVector.push_back(sf::Vertex(vertexPos,
                                       sf::Color(mGradientColor.top.red,
                                                 mGradientColor.top.green,
                                                 mGradientColor.top.blue,
                                                 mGradientColor.top.alpha)));
            } else {
                vertexVector.push_back(sf::Vertex(vertexPos,
                                       sf::Color(mGradientColor.bottom.red,
                                                 mGradientColor.bottom.green,
                                                 mGradientColor.bottom.blue,
                                                 mGradientColor.bottom.alpha)));
            }
        } else {
            vertexVector.push_back(sf::Vertex(vertexPos, mShape.getFillColor()));
        }
    }

    updateEffects();
    window.getWindowPtr()->draw(&vertexVector[0], vertexVector.size(), sf::TrianglesFan, mRenderStates);
}

sf::RectangleShape* Shape::getResourcePointer() {
    return &mShape;
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
    mShape.setFillColor(sf::Color(color.red, color.green,
                                  color.blue, color.alpha));
    mIsGradientColor = false;
}

Color Shape::getColor() {
    return Color(mShape.getFillColor().r, mShape.getFillColor().g,
                 mShape.getFillColor().b, mShape.getFillColor().a);
}

void Shape::setColor(const ColorGradient &color) {
    mIsGradientColor = true;
    mGradientColor   = color;
}

ColorGradient Shape::getColorGradient() {
    return mGradientColor;
}

bool Shape::isColorGradient() {
    return mIsGradientColor;
}

void Shape::setRadius(const float &radius) {
    mRadius = radius;
}

float Shape::getRadius() {
    return mRadius;
}

void Shape::setBorderColor(const Color &color) {
    mShape.setOutlineColor(sf::Color(color.red, color.green,
                                     color.blue, color.alpha));
}

Color Shape::getBorderColor() {
    return Color(mShape.getOutlineColor().r, mShape.getOutlineColor().g,
                 mShape.getOutlineColor().b, mShape.getOutlineColor().a);
}

void Shape::setBorderSize(const float &size) {
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
    return Area(mShape.getLocalBounds().left, mShape.getLocalBounds().top,
                mShape.getLocalBounds().width, mShape.getLocalBounds().height);
}

Area Shape::getGlobalBounds() {
    return Area(mShape.getGlobalBounds().left, mShape.getGlobalBounds().top,
                mShape.getGlobalBounds().width, mShape.getGlobalBounds().height);
}
