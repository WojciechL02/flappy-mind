#include "Bird.h"

Bird::Bird() : gravity(20), flapSpeed(370) {
    texture.loadFromFile("../assets/yellowbird-upflap.png");
    birdSprite.setTexture(texture);
    resetBirdPosition();
}

void Bird::resetBirdPosition() {
    birdSprite.setPosition(80.f, 150.f);
    velocity = 0;
}

void Bird::flap(sf::Time &time) {
    velocity = -flapSpeed * time.asSeconds();
}

void Bird::update(sf::Time &time) {
    if (birdSprite.getGlobalBounds().top < 376) {
        velocity += gravity * time.asSeconds();
        birdSprite.move(0, velocity);
        if (birdSprite.getGlobalBounds().top < 0) {
            birdSprite.setPosition(80.f, 0.f);
        }
    }
}
