#pragma once

#include "State.h"


// Estado de derrota. Al perder, el jugador vuelve a la escena de menu
class LoseMatchState : public State {
public:
    LoseMatchState(CaromScene* scene);

    bool checkCondition(State*& state);
    void onStateEnter() override;
    void onStateExit() override;
};