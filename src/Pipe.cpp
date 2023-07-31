#include "Pipe.h"

Pipe::Pipe(int posY) {
    spriteDown.setTexture(textureDown);
    spriteDown.setPosition(288.f, posY);

    spriteUp.setTexture(textureUp);
    spriteUp.setPosition(288.f, posY - distanceY - spriteUp.getGlobalBounds().height);
}

void Pipe::loadTextures() {
    textureDown.loadFromFile("../assets/pipe-down.png");
    textureUp.loadFromFile("../assets/pipe-up.png");
}

float Pipe::getRightBound() {
    return spriteDown.getGlobalBounds().left + spriteDown.getGlobalBounds().width;
}

void Pipe::update(sf::Time &time) {
    spriteDown.move(-moveSpeed * time.asSeconds(), 0.f);
    spriteUp.move(-moveSpeed * time.asSeconds(), 0.f);
}

sf::Texture Pipe::textureDown, Pipe::textureUp;
