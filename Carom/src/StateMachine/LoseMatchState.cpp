#include "LoseMatchState.h"
#include "CaromScene.h"
#include "ScenesManager.h"
#include "NullState.h"
#include "GameScene.h"

LoseMatchState::LoseMatchState(CaromScene* scene) : State(scene)
{

}

void LoseMatchState::onStateEnter() {

    _scene->getScenesManager()->invokeLose();
}

void LoseMatchState::onStateExit() {

}

bool LoseMatchState::checkCondition(State*& state) {
    
    state = new NullState(_scene);
    return true;
}