#pragma once
#include "GameState.h"

class Agent {
public:
    Agent() = default;
    virtual bool act(GameState &gameState) = 0;
};
