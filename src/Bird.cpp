#include "Bird.h"

Bird::Bird() : gravity(20), flapSpeed(370), animTickCounter(0), textureIdx(1) {
    textures[0].loadFromFile("../assets/yellowbird-downflap.png");
    textures[1].loadFromFile("../assets/yellowbird-midflap.png");
    textures[2].loadFromFile("../assets/yellowbird-upflap.png");

    birdSprite.setTexture(textures[0]);
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
        // ANIMATION
        makeAnimation();

        // MOVE
        velocity += gravity * time.asSeconds();
        birdSprite.move(0, velocity);
        if (birdSprite.getGlobalBounds().top < 0) {
            birdSprite.setPosition(80.f, 0.f);
        }
    }
}

void Bird::makeAnimation() {
    if (animTickCounter == 5) {
        birdSprite.setTexture(textures[textureIdx]);
        textureIdx++;
        if (textureIdx == 3) {
            textureIdx = 0;
        }
        animTickCounter = 0;
    }
    animTickCounter++;
}
