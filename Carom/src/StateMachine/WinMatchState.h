#pragma once

#include "State.h"

class CaromScene;

//Este estado se llama cuando se ha ganado una partida de carambola
class WinMatchState : public State {
public:
    WinMatchState(CaromScene* scene);

    bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;  
};