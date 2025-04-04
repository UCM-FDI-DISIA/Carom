#pragma once

#include "State.h"

// Forward declarations
class CaromScene;

class HitState: public State {
public:
    HitState(CaromScene* scene);
    bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;
};
