#include "GameManager.h"
#include "GameState.h"
#include "Pipe.h"

GameManager::GameManager(sf::RenderWindow &win, Agent &agent) : window(win),
                                                                agent(agent),
                                                                pipesSpawnTime(81),
                                                                pipesCounter(80),
                                                                score(0),
                                                                runGame(true),
                                                                isAlive(true),
                                                                canAddPoint(true) {
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
    updateScore();
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
                score++;
                scoreText.setString("Score: " + std::to_string(score));
                canAddPoint = false;
            }
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
    window.draw(scoreText);
}

bool GameManager::isRunNewGame() const {
    if (runGame) {
        return true;
    }
    return false;
}

void GameManager::resetGameConfiguration() {
    bird.resetBirdPosition();
    isAlive = true;
    pipesCounter = 80;
    pipes.clear();
    score = 0;
    scoreText.setString("Score: 0");
}
