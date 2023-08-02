#include "Button.h"
#include <iostream>

Button::Button(float posX, float posY, sf::Texture &texture) {
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
}

bool Button::isPressed(float x, float y) const {
    auto pos = sprite.getGlobalBounds();
    if (x > pos.left && x < pos.left + pos.width && y > pos.top && y < pos.top + pos.height) {
        return true;
    }
    return false;
}
