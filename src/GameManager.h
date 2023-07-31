#pragma once
#include <SFML/Graphics.hpp>
#include "Agent.h"

class GameManager {
public:
    GameManager(sf::RenderWindow &win, Agent &agent);
    void startGame();

    sf::RenderWindow &window;

private:
//    void processing();
//    void moveGround();
//    void movePipes();
//    void checkCollision();
//    void updateScore();
//    void restartGame();
//    void draw();
    Agent &agent;
};
