#pragma once
#include "GameState.h"

class Agent {
public:
    Agent() = default;
    virtual ~Agent() = default;
    virtual bool act(GameState &gameState) = 0;
};
