#include "HumanAgent.h"

bool HumanAgent::act(GameState &gameState) {
    auto event = gameState.event;
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            return true;
        }
    }
    return false;
}
