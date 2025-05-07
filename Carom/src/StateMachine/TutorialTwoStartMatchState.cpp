#include "TutorialTwoStartMatchState.h"
#include "TutorialTwoHitState.h"
#include "BossState.h"
#include "CaromScene.h"

TutorialTwoStartMatchState::TutorialTwoStartMatchState(CaromScene* scene): StartMatchState(scene) {

}
bool
TutorialTwoStartMatchState::checkCondition(State*& state) {
    if(_finished) { // animación terminada
        state = new TutorialTwoHitState(_scene);
    }
    return _finished;
}