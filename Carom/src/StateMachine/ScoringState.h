#pragma once

#include "State.h"

class ScoringState: public State {
public:
    ScoringState(CaromScene* scene);
    virtual bool checkCondition(State*& state) override;

    virtual void onStateEnter() override;
    void onStateExit() override;
};

