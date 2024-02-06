#include "QLearningAgent.h"
#include <iostream>

QLearningAgent::QLearningAgent(double epsilon, double discount, double lr, bool isTraining) : epsilon(epsilon),
                                                                                              discount(discount),
                                                                                              lr(lr),
                                                                                              isTraining(isTraining),
                                                                                              lastAction(0),
                                                                                              timer(0),
                                                                                              lastState(std::vector<int>{6, 0, 0}) {
    if (!isTraining) {
        loadQFunction();
    }
}

bool QLearningAgent::act(GameState &gameState) {
    timer++;
    if (timer >= 3) {
        timer = 0;
        if (isTraining) {
            return act_train(gameState.getState(), gameState.getReward(), gameState.getIsTerminal());
        }
        return act_test(gameState.getState());
    }
    return false;
}

bool QLearningAgent::act_train(std::vector<int> newState, double reward, bool isTerminal) {
    if (isTerminal) {
//        std::cout << "Terminal: " << reward << " | State: " << lastState[0] << " " << lastState[1] << " " << lastState[2] << std::endl;
    }

    int newAction;
    if (dist(rd) < epsilon) {
        // random action
        newAction = dist(rd) < 0.5 ? 0 : 1;
    } else {
        newAction = getBestAction(newState);
    }
//    std::cout << "State: " << newState[0] << " " << newState[1] << " " << newState[2] << std::endl;

    double update;
    if (!isTerminal) {
        update = reward + discount * getMaxQValue(newState) - getLastQValue();
    } else {
        update = reward - getLastQValue();
    }
    std::cout << "Before: " << Q[lastState[0]][lastState[1]][lastState[2]][lastAction];
    Q[lastState[0]][lastState[1]][lastState[2]][lastAction] += lr * update;
    std::cout << " | After: " << Q[lastState[0]][lastState[1]][lastState[2]][lastAction] << std::endl;

    lastAction = newAction;
    lastState = newState;
    return static_cast<bool>(newAction);
}

bool QLearningAgent::act_test(std::vector<int> newState) {
    return getBestAction(newState);
}

void QLearningAgent::loadQFunction() {
    // TODO: read table from file
}

int QLearningAgent::getBestAction(std::vector<int> state) {
    if (Q[state[0]][state[1]][state[2]][0] > Q[state[0]][state[1]][state[2]][1]) {
        return 0;
    }
    return 1;
}

double QLearningAgent::getMaxQValue(std::vector<int> state) {
    double maxVal = 0;
    for (auto e: Q[state[0]][state[1]][state[2]]) {
        if (e > maxVal) {
            maxVal = e;
        }
    }
    return maxVal;
}

double QLearningAgent::getLastQValue() {
    return Q[lastState[0]][lastState[1]][lastState[2]][lastAction];
}

int QLearningAgent::getTimer() {
    return timer;
}
