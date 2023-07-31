#include "GameManager.h"
#include "GameState.h"

GameManager::GameManager(sf::RenderWindow &win, Agent &agent) : window(win), agent(agent) {}

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
                window.close();
            }
        }

//        processing();
//        draw();
        window.display();
    }
}

//void GameManager::processing() {
//    // TODO: move ground, pipes and bird
//}
//
//void GameManager::draw() {
//    // TODO: draw all stuff
//}
