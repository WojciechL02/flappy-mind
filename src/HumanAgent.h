#pragma once
#include <SFML/Graphics.hpp>
#include "Agent.h"
#include "GameState.h"

class HumanAgent : public Agent {
public:
    HumanAgent() = default;
    bool act(GameState &gameState) override;
    int getTimer() override {
        return 0;
    }
};
