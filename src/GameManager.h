#pragma once
#include <SFML/Graphics.hpp>
#include "Agent.h"
#include "Bird.h"
#include "Pipe.h"

class GameManager {
public:
    GameManager(sf::RenderWindow &win, Agent &agent);
    void startGame();

    sf::RenderWindow &window;

private:
    void processing(sf::Time &time);
    void moveBase(sf::Time &time);
//    void movePipes();
//    void checkCollision();
//    void updateScore();
//    void restartGame();
    void draw();

    Agent &agent;
    sf::Texture bgTexture, baseTexture;
    sf::Sprite bgSprite, baseSprite1, baseSprite2;
    Bird bird;
    std::vector<Pipe> pipes;
    const float moveSpeed = 270.f;
};
