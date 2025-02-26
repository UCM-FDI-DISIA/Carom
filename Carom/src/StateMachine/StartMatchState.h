#pragma once

#include "State.h"

class StartMatchState: public State {
public:
    StartMatchState(CaromScene* scene);
    bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;
};

