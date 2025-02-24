#pragma once
#include "State.h"

class HitState: public State {
public:

    bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;
};

