#pragma once
#include "HitState.h"


class TutorialOneHitState: public HitState {
    public:
    bool checkCondition(State*& state) override;

    TutorialOneHitState(CaromScene* scene);
};