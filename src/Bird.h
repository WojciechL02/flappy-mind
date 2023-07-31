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
    sf::Texture texture;
    float velocity, flapSpeed, gravity;
};
