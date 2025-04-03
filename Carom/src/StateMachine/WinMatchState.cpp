#include "WinMatchState.h"
#include "CaromScene.h"
#include "ScenesManager.h"
#include "NullState.h"

WinMatchState::WinMatchState(CaromScene* scene) : State(scene) 
{

}

void WinMatchState::onStateEnter(){
    auto scene = _scene->getRewardScene();
    _scene->getScenesManager()->pushScene(scene);
}

void WinMatchState::onStateExit() {
    _scene->getScenesManager()->popScene();
}

bool WinMatchState::checkCondition(State*& state) {
    state = new NullState(_scene);
    return true;
}