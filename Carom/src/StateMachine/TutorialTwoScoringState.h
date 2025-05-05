#pragma once
#include "ScoringState.h"

class CaromScene;

class TutorialTwoScoringState: public ScoringState{
public:
    TutorialTwoScoringState(CaromScene* scene);

    bool checkCondition(State*& state) override;
    void onStateEnter() override {}
    void onStateExit() override;
};