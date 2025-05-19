#pragma once

#include "State.h"

/// @brief Estado de puntuación. Aquí se calculan los puntos obtenidos por colisiones de bolas
/// ScoringState -> AddScoreState
class ScoringState: public State {
public:
    ScoringState(CaromScene* scene);
    virtual bool checkCondition(State*& state) override;

    virtual void onStateEnter() override;
    virtual void onStateExit() override;
};

