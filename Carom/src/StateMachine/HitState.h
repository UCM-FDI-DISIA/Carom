#pragma once

#include "State.h"

// Forward declarations
class CaromScene;

// Estado de tirada en el que se espera que el jugador juegue tirando a la bola blanca
class HitState: public State {
public:
    HitState(CaromScene* scene);
    virtual bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;
};
