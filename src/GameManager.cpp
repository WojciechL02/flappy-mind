#include "GameManager.h"
#include "GameState.h"
#include "Pipe.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow &win, Agent &agent) : window(win),
                                                                agent(agent),
                                                                pipesSpawnTime(81),
                                                                pipesCounter(80),
                                                                score(0),
                                                                runGame(true) {
    bgTexture.loadFromFile("../assets/background-day.png");
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(0.f, 0.f);

    baseTexture.loadFromFile("../assets/base.png");
    baseSprite1.setTexture(baseTexture);
    baseSprite1.setPosition(0.f, 400.f);

    baseSprite2.setTexture(baseTexture);
    baseSprite2.setPosition(baseSprite1.getGlobalBounds().width, 400.f);

    Pipe::loadTextures();
}

void GameManager::startGame() {
    sf::Clock clock;
    while (window.isOpen() && runGame) {
        sf::Time time = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // TODO: create game state
            GameState state(event);

            if (agent.act(state)) {
                bird.flap(time);
            }
        }

        processing(time);
        draw();
        window.display();
    }
}

void GameManager::processing(sf::Time &time) {
    moveBase(time);
    if (pipesCounter > pipesSpawnTime) {
        pipes.push_back(Pipe(dist(rd)));
        pipesCounter = 0;
    }
    pipesCounter++;
    for (int i = 0; i < pipes.size(); i++) {
        pipes[i].update(time);
        if (pipes[i].getRightBound() <= 0) {
            pipes.erase(pipes.begin());
        }
    }
    checkCollision();
    bird.update(time);
}

void GameManager::moveBase(sf::Time &time) {
    baseSprite1.move(-moveSpeed * time.asSeconds(), 0.f);
    baseSprite2.move(-moveSpeed * time.asSeconds(), 0.f);

    if (baseSprite1.getGlobalBounds().left + baseSprite1.getGlobalBounds().width <= 0) {
        baseSprite1.setPosition(baseSprite2.getGlobalBounds().left + baseSprite2.getGlobalBounds().width, 400.f);
    } else if (baseSprite2.getGlobalBounds().left + baseSprite2.getGlobalBounds().width <= 0) {
        baseSprite2.setPosition(baseSprite1.getGlobalBounds().left + baseSprite1.getGlobalBounds().width, 400.f);
    }
}

void GameManager::checkCollision() {
    if (pipes.size() > 0) {
        if (pipes[0].spriteDown.getGlobalBounds().intersects(bird.birdSprite.getGlobalBounds()) ||
            pipes[0].spriteUp.getGlobalBounds().intersects(bird.birdSprite.getGlobalBounds()) ||
            bird.birdSprite.getGlobalBounds().top + bird.birdSprite.getGlobalBounds().width > 400.f) {
            runGame = false;
        }
    }
}

void GameManager::draw() {
    // TODO: draw all the stuff
    window.draw(bgSprite);
    for (auto &pipe: pipes) {
        window.draw(pipe.spriteDown);
        window.draw(pipe.spriteUp);
    }
    window.draw(baseSprite1);
    window.draw(baseSprite2);
    window.draw(bird.birdSprite);
}
