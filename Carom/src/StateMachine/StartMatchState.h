#pragma once

#include "State.h"

// Forward declarations
class CaromScene;

/// @brief Estado de inicio de partida.
/// StartMatchState -> BossState o HitState en función de si es o no partida de Boss
class StartMatchState: public State {
protected:
    bool _finished = true;
public:
    StartMatchState(CaromScene* scene);
    virtual bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;

    inline void finish() override {_finished = true; }
};
