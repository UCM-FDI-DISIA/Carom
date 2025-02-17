#include "WinMatchState.h"
#include "CaromScene.h"
#include "ScenesManager.h"

WinMatchState::WinMatchState(CaromScene* scene) : State(scene) 
{

}

void WinMatchState::onStateEnter(){
    _scene->getScenesManager()->pushScene(_scene->getRewardScene());
}

void WinMatchState::onStateExit() {
    _scene->getScenesManager()->popScene();
}

bool WinMatchState::checkCondition(State*& state) {

}