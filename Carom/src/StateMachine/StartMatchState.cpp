#include "StartMatchState.h"
#include "HitState.h"
#include "BossState.h"
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
    if(_finished) { // animación terminada
        if(_scene->isBossMatch())
            state = new BossState(_scene);
        else state = new HitState(_scene);
    }
    return _finished;
}