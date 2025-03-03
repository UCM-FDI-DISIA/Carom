#include "StartMatchState.h"
#include "HitState.h"

StartMatchState::StartMatchState(ecs::CaromScene* scene): State(scene) {

}

void
StartMatchState::onStateEnter() {
    // TODO: mostrar puntuación
}

void 
StartMatchState::onStateExit() {

}

bool
StartMatchState::checkCondition(State*& state) {
    // if(animación terminada) {
        state = new HitState(_scene);
        return true;
    // }
    return false;
}