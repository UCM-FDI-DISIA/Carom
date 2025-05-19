#pragma once

#include "State.h"


class CaromScene;

/// @brief Estado de acción del boss. Aquí elimina y aplica sus modificadores de partida
/// Solo se pasa a este estado cuando es una partida de boss.
/// BossState -> HitState
class BossState: public State {
protected:
    bool _finished = false;
public:
    BossState(CaromScene* scene);

    bool checkCondition(State*& state) override;
    void onStateEnter() override;
    void onStateExit() override;

    inline void finish() override {_finished = true; }
};

