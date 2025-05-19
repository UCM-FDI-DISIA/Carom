#pragma once

#include "State.h"

/// @brief Estado de puntuación. Aquí se calculan los puntos obtenidos por colisiones de bolas
/// ScoringState -> WinMatchState / LoseMathcState si se gana o se pierde la partida. Si no:
/// ScoringState -> HitState o BossState, en función de si es una partida de Boss
class ScoringState: public State {
public:
    ScoringState(CaromScene* scene);
    virtual bool checkCondition(State*& state) override;

    virtual void onStateEnter() override;
    virtual void onStateExit() override;
};

