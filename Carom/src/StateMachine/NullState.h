#include "State.h"

namespace ecs{
    class CaromScene;
}
//Estado a devolver en un checkCondition como alternativa a no devolver nada, para no romper el flujo
class NullState : public State{
public:
    inline NullState(ecs::CaromScene* scene) : State(scene) {}

    inline void update() override {}
    inline bool checkCondition(State*& state) override {return false;}
    inline void onStateEnter() override {};
    inline void onStateExit() override {};
};