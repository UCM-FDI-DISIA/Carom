#pragma once

#include "State.h"


class CaromScene;

// Estado de boss en el que este ejecuta su acción
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

