#include "TutorialTwoHitState.h"
#include "CaromScene.h"
#include "NullState.h"
#include "ScenesManager.h"
#include "TutorialTwoScoringState.h"

TutorialTwoHitState::TutorialTwoHitState(CaromScene* scene): HitState(scene){

}

bool TutorialTwoHitState::checkCondition(State*& state){
    if(HitState::checkCondition(state)){

        // En hit state se está creando un estado, estado que no se estaba destruyendo
        // y estado que no se va a usar, esto es un apaño
        delete state;

        state = new TutorialTwoScoringState(_scene);
        return true;
    }
    return false;
}