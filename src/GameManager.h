#pragma once
#include <SFML/Graphics.hpp>
#include <random>
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
    void checkCollision();
//    void updateScore();
//    void restartGame();
    void draw();

    Agent &agent;
    sf::Texture bgTexture, baseTexture;
    sf::Sprite bgSprite, baseSprite1, baseSprite2;
    Bird bird;
    std::vector<Pipe> pipes;
    const int pipesSpawnTime;
    int pipesCounter, score;
    const float moveSpeed = 140.f;
    bool runGame;
    std::random_device rd;
    std::uniform_int_distribution<int> dist{150,350};
};
