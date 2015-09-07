#include "Shape.h"
#include "cmath"

using namespace ME;

Shape::Shape(const Vect2f& size, const Color& color, const Vect2f& pos) {
    m_type = Resource::Type::SHAPE;

    setSize(size);
    setColor(color);
    setPosition(pos);
    mIsGradientColor = false;
    mRadius          = 0.0f;
    mNumberPoints    = 30;
}


void Shape::draw(Window& window, sf::RenderStates* state) {

}

void Shape::draw(sf::RenderWindow* renderWindow, sf::RenderStates* state) {
    std::vector<sf::Vertex> vertexVector;

    sf::Vector2f shapeSize(getSize().x, getSize().y);

    // Se o radius for maior que a metade do menor tamanho (width ou hight)
    // causa problemas então a gente reseta para a melhor opção possivel
    // Já que o tamanho máximo de radius é de 50%, criando um circulo
    // maior do que isso causa comportamento inesperado
    if (mRadius > 0.0f) {
        float shapeMinSize = std::min(shapeSize.x, shapeSize.y) / 2;
        if (mRadius > shapeMinSize) {
            mRadius = shapeMinSize;
        }
    }

    for(int i = 0; i < mNumberPoints * 4; i++) {

        float deltaAngle = 90.0f / (mNumberPoints - 1);
        sf::Vector2f center;
        unsigned int centerIndex = i / mNumberPoints;
        static const float PI = 3.141592654f;

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
                     (i - centerIndex) * PI / 180) + center.x + shapePos.x;

        float posY = -mRadius * std::sin(deltaAngle *
                     (i - centerIndex) * PI / 180) + center.y + shapePos.y;

        sf::Vector2f vertexPos = sf::Vector2f(posX, posY);

        if(mIsGradientColor) {
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

    if (state == nullptr) {
        state = updateEffects();
    }

    renderWindow->draw(&vertexVector[0], vertexVector.size(), sf::TrianglesFan, *state);
}

sf::RectangleShape* Shape::getResourcePointer() {
    return &mShape;
}

void Shape::setPosition(const Vect2f& pos) {
    mShape.setPosition(sf::Vector2f(pos.x, pos.y));
}

Vect2f Shape::getPosition() {
    return Vect2f(mShape.getPosition().x, mShape.getPosition().y);
}

void Shape::move(const Vect2f& pos) {
    mShape.move(sf::Vector2f(pos.x, pos.y));
}

void Shape::setSize(const Vect2f& size) {
    mShape.setSize(sf::Vector2f(size.x, size.y));
}

Vect2f Shape::getSize() {
    return Vect2f(mShape.getSize().x, mShape.getSize().y);
}

Vect2f Shape::getScale() {
    return Vect2f(mShape.getScale().x, mShape.getScale().y);
}

void Shape::setScale(const Vect2f& scale) {
    mShape.setScale(sf::Vector2f(scale.x, scale.y));
}

void Shape::setColor(const Color& color) {
    mShape.setFillColor(sf::Color(color.red, color.green,
                                  color.blue, color.alpha));
    mIsGradientColor = false;
}

Color Shape::getColor() {
    return Color(mShape.getFillColor().r, mShape.getFillColor().g,
                 mShape.getFillColor().b, mShape.getFillColor().a);
}

void Shape::setColor(const ColorGradient& color) {
    mIsGradientColor = true;
    mGradientColor   = color;
}

ColorGradient Shape::getColorGradient() {
    return mGradientColor;
}

bool Shape::isColorGradient() {
    return mIsGradientColor;
}

void Shape::setRadius(const float& radius) {
    mRadius = radius;
}

float Shape::getRadius() {
    return mRadius;
}

void Shape::setBorderColor(const Color& color) {
    mShape.setOutlineColor(sf::Color(color.red, color.green,
                                     color.blue, color.alpha));
}

Color Shape::getBorderColor() {
    return Color(mShape.getOutlineColor().r, mShape.getOutlineColor().g,
                 mShape.getOutlineColor().b, mShape.getOutlineColor().a);
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

void Shape::setRotation(const float& angle) {
    mShape.setRotation(angle);
}

void Shape::rotate(const float& angle) {
    mShape.rotate(angle);
}

Vect2f Shape::getOrigin() {
    return Vect2f(mShape.getOrigin().x, mShape.getOrigin().y);
}

void Shape::setOrigin(const Vect2f& origin) {
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
