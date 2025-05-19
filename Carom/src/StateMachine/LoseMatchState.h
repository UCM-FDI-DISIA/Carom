#pragma once

#include "State.h"

/// @brief Estado de derrota. Al perder, salta la escena de derrota.
class LoseMatchState : public State {
public:
    LoseMatchState(CaromScene* scene);

    bool checkCondition(State*& state);
    void onStateEnter() override;
    void onStateExit() override;
};