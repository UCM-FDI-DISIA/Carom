#include "TutorialOneHitState.h"
#include "CaromScene.h"
#include "NullState.h"
#include "ScenesManager.h"
#include "TutorialOneScoringState.h"

TutorialOneHitState::TutorialOneHitState(CaromScene* scene): HitState(scene){

}

bool TutorialOneHitState::checkCondition(State*& state){
    if(HitState::checkCondition(state)){

        // En hit state se está creando un estado, estado que no se estaba destruyendo
        // y estado que no se va a usar, esto es un apaño
        delete state;
        
        state = new TutorialOneScoringState(_scene);
        return true;
    }
    return false;
}