#include "StartMatchState.h"
#include "HitState.h"
#include "BossState.h"
#include "CaromScene.h"

StartMatchState::StartMatchState(CaromScene* scene): State(scene) {

}

void
StartMatchState::onStateEnter() {
    #ifdef _DEBUG
        std::cout << "start match state" << std::endl;
    #endif
    
    setBallInputActive(false);
    setStickActive(false);
    setAimLineActive(false);
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