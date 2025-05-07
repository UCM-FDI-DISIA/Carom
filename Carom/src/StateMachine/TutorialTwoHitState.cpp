#include "TutorialTwoHitState.h"
#include "CaromScene.h"
#include "NullState.h"
#include "ScenesManager.h"
#include "TutorialTwoScoringState.h"

TutorialTwoHitState::TutorialTwoHitState(CaromScene* scene): HitState(scene){

}

bool TutorialTwoHitState::checkCondition(State*& state){
    if(HitState::checkCondition(state)){
        state = new TutorialTwoScoringState(_scene);
        return true;
    }
    return false;
}