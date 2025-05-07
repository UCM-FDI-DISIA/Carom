#include "TutorialOneStartMatchState.h"
#include "TutorialOneHitState.h"
#include "BossState.h"
#include "CaromScene.h"

TutorialOneStartMatchState::TutorialOneStartMatchState(CaromScene* scene): StartMatchState(scene) {

}
bool
TutorialOneStartMatchState::checkCondition(State*& state) {
    if(_finished) { // animación terminada
        state = new TutorialOneHitState(_scene);
    }
    return _finished;
}