#pragma once

#include "State.h"

class CaromScene;

/// @brief Estado de victoria. Se llama cuando se gana la partida de carambola
class WinMatchState : public State {
public:
    WinMatchState(CaromScene* scene);

    bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;  
};