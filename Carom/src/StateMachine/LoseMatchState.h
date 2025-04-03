#pragma once

#include "State.h"

class LoseMatchState : public State {
public:
    LoseMatchState(CaromScene* scene);

    bool checkCondition(State*& state);
    void onStateEnter() override;
    void onStateExit() override;
};