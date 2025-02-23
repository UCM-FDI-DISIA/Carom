#include "State.h"

namespace ecs{
    class CaromScene;
}

class PL_State : public State
{
public: 
    PL_State(ecs::CaromScene* scene): State(scene){}

    void update() override {}

    bool checkCondition(State*& state) override { return false; }

    //se ejecuta cuando se entra al estado
    void onStateEnter() override {}
    //se ejecuta cuando se sale del estado
    void onStateExit() override {}
};