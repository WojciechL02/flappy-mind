#pragma once
#include <SFML/Graphics.hpp>

class Button {
public:
    Button() = default;
    Button(float posX, float posY, sf::Texture &texture);
    bool isPressed(float x, float y) const;

    sf::Sprite sprite;
};
