#include "GameManager.h"
#include "GameState.h"

GameManager::GameManager(sf::RenderWindow &win, Agent &agent) : window(win), agent(agent) {
    bgTexture.loadFromFile("../assets/background-day.png");
    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(0.f, 0.f);

    baseTexture.loadFromFile("../assets/base.png");
    baseSprite1.setTexture(baseTexture);
    baseSprite1.setPosition(0.f, 400.f);

    baseSprite2.setTexture(baseTexture);
    baseSprite2.setPosition(baseSprite1.getGlobalBounds().width, 400.f);
}

void GameManager::startGame() {
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time time = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // TODO: create game state
            GameState state(event);

            if (agent.act(state)) {
                // TODO: bird jump
                bird.flap(time);
            }
        }

        processing(time);
        draw();
        window.display();
    }
}

void GameManager::processing(sf::Time &time) {
    // TODO: move ground, pipes and bird
    moveBase(time);
    bird.update(time);
}

void GameManager::moveBase(sf::Time &time) {
    baseSprite1.move(-moveSpeed * time.asSeconds(), 0.f);
}

void GameManager::draw() {
    // TODO: draw all stuff
    window.draw(bgSprite);
    window.draw(baseSprite1);
    window.draw(baseSprite2);
    window.draw(bird.birdSprite);
}
