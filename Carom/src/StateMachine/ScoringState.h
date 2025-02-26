#pragma once

#include "State.h"

class ScoringState: public State {
public:
    ScoringState(CaromScene* scene);
    bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;
};

