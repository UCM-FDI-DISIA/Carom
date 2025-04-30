#include "TutorialOneHitState.h"
#include "CaromScene.h"
#include "NullState.h"
#include "ScenesManager.h"

TutorialOneHitState::TutorialOneHitState(CaromScene* scene): State(scene){

}

bool TutorialOneHitState::checkCondition(State*& state){
    return _scene->getCurrentScore()>0 || _scene->getRoundScore()>0;
    state = new NullState();
}
void TutorialOneHitState::onStateEnter(){
    
}

void TutorialOneHitState::onStateExit(){
    _scene->getScenesManager()->popScene();
}