#pragma once
#include "State.h"


class CaromScene;

class TutorialOneHitState: public State {
protected:
    bool _finished = false;
public:
    TutorialOneHitState(CaromScene* scene);

    bool checkCondition(State*& state) override;
    void onStateEnter() override;
    void onStateExit() override;

    inline void finish() override {_finished = true; }
};