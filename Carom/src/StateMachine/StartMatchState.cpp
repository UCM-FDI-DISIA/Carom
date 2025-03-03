#include "StartMatchState.h"
#include "HitState.h"
#include "CaromScene.h"

StartMatchState::StartMatchState(ecs::CaromScene* scene): State(scene) {

}

void
StartMatchState::onStateEnter() {
    for(auto& e: _scene->getEntitiesOfGroup(ecs::grp::PALO))
        e->deactivate();
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