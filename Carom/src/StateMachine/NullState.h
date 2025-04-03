#pragma once

#include "State.h"


class CaromScene;
//Estado a devolver en un checkCondition como alternativa a no devolver nada, para no romper el flujo
class NullState : public State{
public:
    inline NullState(CaromScene* scene) : State(scene) {}

    inline bool checkCondition(State*& state) override {return false;}
    inline void onStateEnter() override {};
    inline void onStateExit() override {};
};