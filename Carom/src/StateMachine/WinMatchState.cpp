#include "WinMatchState.h"
#include "CaromScene.h"
#include "ScenesManager.h"
#include "NullState.h"

WinMatchState::WinMatchState(ecs::CaromScene* scene) : State(scene) 
{

}

void WinMatchState::onStateEnter(){
    _scene->getScenesManager()->pushScene(_scene->getRewardScene());
}

void WinMatchState::onStateExit() {
    _scene->getScenesManager()->popScene();
}

bool WinMatchState::checkCondition(State*& state) {
    state = new NullState(_scene);
    return true;
}