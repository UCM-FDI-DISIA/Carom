#pragma once

#include "State.h"

//Este estado se llama cuando se ha ganado una partida de carambola
class WinMatchState : public State {
public:
    WinMatchState(CaromScene* scene);

    void update() override {}

    bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;  
};