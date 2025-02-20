#pragma once
#include "State.h"

// Estado de resolución de golpe
class PostScoringState: public State {
public:
    inline PostScoringState(CaromScene* scene): State(scene){};

    bool checkCondition(State*& state) override;

    void onStateEnter() override;
    void onStateExit() override;
};

