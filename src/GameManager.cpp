#include "GameManager.h"
#include "GameState.h"
#include "Pipe.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow &win, Agent *agent) : window(win),
                                                                agent(agent),
                                                                pipesSpawnTime(16),
                                                                pipesCounter(0),
                                                                score(0),
                                                                runGame(true),
                                                                isAlive(true),
                                                                canAddPoint(true),
                                                                scored(false),
                                                                isTerminal(false),
                                                                reward(0.) {
    bgTexture.loadFromFile("../assets/background-day.png");
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(0.f, 0.f);

    baseTexture.loadFromFile("../assets/base.png");
    baseSprite1.setTexture(baseTexture);
    baseSprite1.setPosition(0.f, 400.f);

    baseSprite2.setTexture(baseTexture);
    baseSprite2.setPosition(baseSprite1.getGlobalBounds().width, 400.f);

    font.loadFromFile("../assets/Roboto-Bold.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(15, 15);
    scoreText.setString("Score: 0");

    Pipe::loadTextures();
}

void GameManager::startGame() {
    sf::Clock clock;
    pipes.push_back(Pipe(dist(rd)));

    while (window.isOpen() && runGame && isAlive) {
        sf::Time time = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                runGame = false;
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                runGame = false;
            }
        }

        GameState state(event, bird, pipes, reward, isTerminal);

        if (agent->act(state)) {
            bird.flap(time);
        }
        if (agent->getTimer() == 0) {
            reward = 0.01;
            isTerminal = false;
        }
        processing(time);
        if (scored) {
            std::cout << "Score: " << score << std::endl;
            reward = 1.0;
        }
        scored = false;
        if (!isAlive) {
            reward = -1.0;
            isTerminal = true;
        }
//        std::cout << reward << std::endl;

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
    updateScore();
    bird.update(time);
}

void GameManager::moveBase(sf::Time &time) {
    baseSprite1.move(-moveSpeed * time.asSeconds() * 5, 0.f);
    baseSprite2.move(-moveSpeed * time.asSeconds() * 5, 0.f);

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
            bird.getDownBound() >= 400.f ||
            bird.birdSprite.getGlobalBounds().top <= 0.f) {
            isAlive = false;
        }
    }
}

void GameManager::updateScore() {
    if (pipes.size() > 0) {
        if (!canAddPoint) {
            if (bird.birdSprite.getGlobalBounds().left > pipes[0].spriteDown.getGlobalBounds().left &&
                bird.birdSprite.getGlobalBounds().left + bird.birdSprite.getGlobalBounds().width < pipes[0].getRightBound()) {
                canAddPoint = true;
            }
        } else {
            if (bird.birdSprite.getGlobalBounds().left > pipes[0].getRightBound()) {
                scored = true;
                score++;
                scoreText.setString("Score: " + std::to_string(score));
                canAddPoint = false;
            }
        }
    }
}

void GameManager::draw() {
    window.draw(bgSprite);
    for (auto &pipe: pipes) {
        window.draw(pipe.spriteDown);
        window.draw(pipe.spriteUp);
    }
    window.draw(baseSprite1);
    window.draw(baseSprite2);
    window.draw(bird.birdSprite);
    window.draw(scoreText);
}

bool GameManager::isRunNewGame() const {
    if (runGame) {
        return true;
    }
    return false;
}

void GameManager::resetAgent() {
//    agent = nullptr;
}

void GameManager::resetGameConfiguration() {
    bird.resetBirdPosition();
    isAlive = true;
    pipesCounter = 0;
    pipes.clear();
    score = 0;
    scoreText.setString("Score: 0");
}
