#include "TutorialOneHitState.h"
#include "CaromScene.h"

TutorialOneHitState::TutorialOneHitState(CaromScene* scene): State(scene){

}

bool TutorialOneHitState::checkCondition(State*& state){
    return _scene->getCurrentScore()>0 || _scene->getRoundScore()>0;
}
void TutorialOneHitState::onStateEnter(){
    
}

void TutorialOneHitState::onStateExit(){

}