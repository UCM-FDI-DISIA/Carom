#pragma once

#include "State.h"

namespace ecs {
class CaromScene;
}

class StartMatchState: public State {
protected:
    bool _finished = true; // TODO: por defecto a false, se pone a true cuando termina la animación ->finish()
public:
    StartMatchState(CaromScene* scene);
    bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;

    inline void finish() override {_finished = true; }
};

