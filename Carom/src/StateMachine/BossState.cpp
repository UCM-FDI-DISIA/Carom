#include "BossState.h"
#include "HitState.h"
#include "CaromScene.h"

BossState::BossState(CaromScene* scene): State(scene) {

}

void
BossState::onStateEnter() {
    #ifdef _DEBUG
    std::cout<< "Enter boss state" << std::endl;
    #endif
    _scene->playBossTurn();
}

void 
BossState::onStateExit() {
    #ifdef _DEBUG
    std::cout<< "Exit boss state" << std::endl;
    #endif
}

bool 
BossState::checkCondition(State*& state) {
    if(_finished){
        #ifdef _DEBUG
        std::cout<< "new Hitstate desde boss state" << std::endl;
        #endif
        state = new HitState(_scene);
    }
    return _finished;
}