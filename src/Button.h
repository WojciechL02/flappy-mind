#pragma once
#include <SFML/Graphics.hpp>

class Button {
public:
    Button() = default;
    Button(float posX, float posY, sf::Color color, sf::Vector2f size);
    bool isPressed(float x, float y);

    sf::RectangleShape getShape();

private:
    sf::RectangleShape shape;
};
