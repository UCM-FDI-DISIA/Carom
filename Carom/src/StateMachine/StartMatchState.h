#pragma once

#include "State.h"

// Forward declarations
class CaromScene;

// Estado de inicio de partida en el que se pasa al estado de boss si es boss
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
