#include "TutorialOneHitState.h"
#include "CaromScene.h"
#include "NullState.h"
#include "ScenesManager.h"
#include "TutorialOneScoringState.h"

TutorialOneHitState::TutorialOneHitState(CaromScene* scene): HitState(scene){

}

bool TutorialOneHitState::checkCondition(State*& state){
    if(HitState::checkCondition(state)){
        state = new TutorialOneScoringState(_scene);
        return true;
    }
    return false;
}