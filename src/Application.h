#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class Application {
public:
    explicit Application(sf::RenderWindow &window);
    void run();

    sf::RenderWindow &window;

private:
//    sf::Texture bgTexture;
    Button startGameBtn;
    void draw();
//    void startGame();
};
