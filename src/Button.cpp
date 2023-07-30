#include "Button.h"

Button::Button(float posX, float posY, sf::Color color, sf::Vector2f size) {
    this->shape = sf::RectangleShape(size);
    this->shape.setPosition(posX, posY);
    this->shape.setFillColor(color);
}

sf::RectangleShape Button::getShape() {
    return shape;
}

bool Button::isPressed(float x, float y) {
    auto pos = shape.getPosition();
    auto size = shape.getSize();
    if (x > pos.x && x < pos.x + size.x && y > pos.y && y < pos.y + size.y) {
        return true;
    }
    return false;
}
