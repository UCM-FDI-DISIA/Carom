#pragma once

#include "State.h"

namespace ecs {
class CaromScene;
}

class StartMatchState: public State {
public:
    StartMatchState(ecs::CaromScene* scene);
    bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;
};

