#pragma once
#include <SFML/Graphics.hpp>

class GameState {
public:
    GameState(sf::Event &event);
    sf::Event &event;
};
