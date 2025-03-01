#include "StartMatchState.h"
#include "HitState.h"
#include "CaromScene.h"

StartMatchState::StartMatchState(ecs::CaromScene* scene): State(scene) {

}

void
StartMatchState::onStateEnter() {
    // TODO: mostrar puntuación
    std::cout<<"Start start state"<<std::endl;
}

void 
StartMatchState::onStateExit() {
    std::cout<<"Exit start state"<<std::endl;
}

bool
StartMatchState::checkCondition(State*& state) {
    std::cout <<"start state checkcondition" << std::endl;
    // TODO: cambiar a condición animación terminada
    if(true) {
        state = new HitState(_scene);
        return true;
    }
    return false;
}