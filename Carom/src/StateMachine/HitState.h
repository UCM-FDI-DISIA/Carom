#pragma once

#include "State.h"

// Forward declarations
class CaromScene;

/// @brief Estado de tirada. Se permanece en este estado hasta que el jugador golpee a la bola blanca
/// Hitstate -> ScoringState
class HitState: public State {
public:
    HitState(CaromScene* scene);
    virtual bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;
};
