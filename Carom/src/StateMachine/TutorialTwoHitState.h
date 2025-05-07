#pragma once
#include "HitState.h"


class TutorialTwoHitState: public HitState {
    public:
    bool checkCondition(State*& state) override;

    TutorialTwoHitState(CaromScene* scene);
};