#pragma once
#include <random>
#include "Agent.h"
#include "GameState.h"

class QLearningAgent : public Agent {
public:
    QLearningAgent() = default;
    QLearningAgent(double epsilon, double discount, double lr, bool isTraining);
    bool act(GameState &gameState) override;

private:
    bool act_train(std::vector<int> newState, double reward, bool isTerminal);
    bool act_test(std::vector<int> newState);
    void loadQFunction();
    int getBestAction(std::vector<int> state);
    double getMaxQValue(std::vector<int> state);
    double getLastQValue();
    int getTimer();

    double epsilon, discount, lr;
    bool isTraining;
    double Q[6][11][2][2] = {};
//    double Q[75][2][2][2] = {};
    int lastAction, timer;
    std::vector<int> lastState;
    std::random_device rd;
    std::uniform_real_distribution<double> dist{0.0, 1.0};
};

/*
 * 1. (int) distance from lower right corner to down pipe on X axis (bucketing)
 * 2. (int) ABS distance from lower right to down pipe on Y axis (bucketing)
 * 3. (bool) is above down pipe
 * */
