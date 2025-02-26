#pragma once

#include "State.h"

class HitState: public State {
public:
    HitState(CaromScene* scene);
    bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;
};

