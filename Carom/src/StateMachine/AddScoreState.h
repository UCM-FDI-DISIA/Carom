#pragma once

#include "State.h"

/// @brief Estado de suma de puntos. Se añade la puntuación obtenida en esta ronda a la total
/// AddScoreState -> WinMatchState / LoseMathcState si se gana o se pierde la partida. Si no:
/// AddScoreState -> HitState o BossState, en función de si es una partida de Boss
class AddScoreState: public State {
public:
    AddScoreState(CaromScene* scene);
    virtual bool checkCondition(State*& state) override;

    virtual void onStateEnter() override;
    virtual void onStateExit() override;
};

