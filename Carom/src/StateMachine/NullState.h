#pragma once

#include "State.h"


class CaromScene;
/// @brief Estado a devolver en un checkCondition como alternativa a no devolver nada, para no romper el flujo
class NullState : public State{
public:
    inline NullState(CaromScene* scene = nullptr) : State(scene) {}

    inline bool checkCondition(State*& state) override {return false;}
    inline void onStateEnter() override {};
    inline void onStateExit() override {};
};