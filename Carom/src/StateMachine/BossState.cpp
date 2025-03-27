#include "BossState.h"
#include "HitState.h"
#include "CaromScene.h"

BossState::BossState(ecs::CaromScene* scene): State(scene) {

}

void
BossState::onStateEnter() {
    // std::cout<< "Enter boss state" << std::endl;
    _scene->playBossTurn();
}

void 
BossState::onStateExit() {
    // std::cout<< "Exit boss state" << std::endl;
}

bool 
BossState::checkCondition(State*& state) {
    if(_finished){
        // std::cout<< "new Hitstate" << std::endl;
        state = new HitState(_scene);
    }
    return _finished;
}