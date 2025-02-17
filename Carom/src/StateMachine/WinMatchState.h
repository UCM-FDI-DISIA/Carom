#pragma once

#include "State.h"

class WinMatchState : public State {
public:
    WinMatchState(CaromScene* scene);

    void update() override {}

    bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;  
};