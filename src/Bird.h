#pragma once
#include <SFML/Graphics.hpp>

class Bird {
public:
    Bird();
    void resetBirdPosition();
    void flap(sf::Time &time);
    void update(sf::Time &time);

    sf::Sprite birdSprite;

private:
    void makeAnimation();

    sf::Texture textures[3];
    float velocity, flapSpeed, gravity;
    int animTickCounter, textureIdx;
};
