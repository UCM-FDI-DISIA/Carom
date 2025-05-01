#pragma once
#include "ScoringState.h"

class CaromScene;

class TutorialOneScoringState: public ScoringState{
public:
    TutorialOneScoringState(CaromScene* scene);

    bool checkCondition(State*& state) override;
    void onStateEnter() override {}
};