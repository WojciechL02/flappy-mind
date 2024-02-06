#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bird.h"
#include "Pipe.h"

class GameState {
public:
    GameState(sf::Event &event, Bird &bird, std::vector<Pipe> &pipes, double reward, bool isTerminal);
    std::vector<int> getState();
    double getReward();
    bool getIsTerminal();

    sf::Event &event;

private:
    int bucketingParam, distanceX, distanceY, distanceBase, isAbovePipe, isUpflap;
    double reward;
    bool isTerminal;

    Pipe findNextPipe(Bird &bird, std::vector<Pipe> &pipes);
    int calculateDistanceX(Bird &bird, const Pipe &pipe);
    int calculateDistanceY(Bird &bird, const Pipe &pipe);
    int calculateDistanceBase(Bird &bird);
    int isBirdAbove(Bird &bird, const Pipe &pipe);
    int isBirdUpflap(Bird &bird);
};
