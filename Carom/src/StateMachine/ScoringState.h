#pragma once

#include "State.h"

// Estado de puntuación en el que el jugador termina de tirar (después de hit state) y la puntución por la colisiones ocurre
class ScoringState: public State {
public:
    ScoringState(CaromScene* scene);
    virtual bool checkCondition(State*& state) override;

    virtual void onStateEnter() override;
    virtual void onStateExit() override;
};

