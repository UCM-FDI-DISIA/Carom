#pragma once
#include "State.h"

class ScoringState: public State {
public:

    virtual void update() override;

    bool checkCondition(State*& state) override;


    void onStateEnter() override;
    void onStateExit() override;
};

