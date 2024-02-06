#pragma once
#include <SFML/Graphics.hpp>

class Pipe {
public:
    explicit Pipe(int posY);
    static void loadTextures();
    float getRightBound();
    void update(sf::Time &time);

    sf::Sprite spriteDown, spriteUp;

private:
    static sf::Texture textureDown, textureUp;
    static const int distanceY = 140, moveSpeed = 80;
};
