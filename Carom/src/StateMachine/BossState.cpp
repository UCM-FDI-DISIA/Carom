#include "BossState.h"
#include "HitState.h"
#include "CaromScene.h"

BossState::BossState(CaromScene* scene): State(scene) {

}

void
BossState::onStateEnter() {
    _scene->playBossTurn();
}

void 
BossState::onStateExit() {

}

bool 
BossState::checkCondition(State*& state) {
    if(_finished)
        state = new HitState(_scene);
    return _finished;
}