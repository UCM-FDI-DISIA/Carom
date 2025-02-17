#pragma once

#include "State.h"

class EndMatchState : public State {
public:
    void update() override {}

    bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;
};