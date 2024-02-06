#include "GameState.h"
#include <iostream>

GameState::GameState(sf::Event &event, Bird &bird, std::vector<Pipe> &pipes, double reward, bool isTerminal) : event(event), bucketingParam(30) {
    const Pipe &nextPipe = findNextPipe(bird, pipes);
    distanceX = calculateDistanceX(bird, nextPipe);
    distanceY = calculateDistanceY(bird, nextPipe);
    distanceBase = calculateDistanceBase(bird);
    isAbovePipe = isBirdAbove(bird, nextPipe);
    isUpflap = isBirdUpflap(bird);
    this->reward = reward;
    this->isTerminal = isTerminal;
}

std::vector<int> GameState::getState() {
//    return std::vector<int> {distanceX, distanceY, distanceBase, isAbovePipe, isUpflap};
    return std::vector<int> {distanceX, distanceY, isAbovePipe};
}

double GameState::getReward() {
    return reward;
}

bool GameState::getIsTerminal() {
    return isTerminal;
}

Pipe GameState::findNextPipe(Bird &bird, std::vector<Pipe> &pipes) {
    for (auto &pipe : pipes) {
        if (bird.birdSprite.getGlobalBounds().left < pipe.getRightBound()) {
            return pipe;
        }
    }
}

int GameState::calculateDistanceX(Bird &bird, const Pipe &pipe) {
//    if (pipe.spriteDown.getGlobalBounds().left <= bird.birdSprite.getGlobalBounds().left) {
//        return 0;
//    }
    int res = static_cast<int> ((pipe.spriteDown.getGlobalBounds().left - bird.getRightBound()) / bucketingParam);
    if (res < 0) {
        return 0;
    }
    return res;
}

int GameState::calculateDistanceY(Bird &bird, const Pipe &pipe) {
    int value = static_cast<int> (pipe.spriteDown.getGlobalBounds().top - bird.getDownBound());
    return abs(value) / bucketingParam;
}

int GameState::calculateDistanceBase(Bird &bird) {
    return static_cast<int> ((400.0 - bird.getDownBound()) / bucketingParam);
}

int GameState::isBirdAbove(Bird &bird, const Pipe &pipe) {
    if (pipe.spriteDown.getGlobalBounds().top > bird.getDownBound()) {
        return 1;
    }
    return 0;
}

int GameState::isBirdUpflap(Bird &bird) {
    if (bird.getVelocity() < 0.0) {
        return 1;
    }
    return 0;
}
