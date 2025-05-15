#include "WinMatchState.h"
#include "CaromScene.h"
#include "ScenesManager.h"
#include "NullState.h"
#include "JsonEntityParser.h"
#include "InventoryManager.h"
#include "PoolScene.h"
#include "AudioManager.h"
#include "EndGameScene.h"

WinMatchState::WinMatchState(CaromScene* scene) : State(scene) 
{
}

void WinMatchState::onStateEnter(){
    #ifndef _DEBUG
    #endif
    //AudioManager::Instance()->changeToPauseTheme();
    InventoryManager::Instance()->saveBalls(_scene->getEntitiesOfGroup(grp::EFFECTBALLS));
    //deberia popear escena
    //auto scene = _scene->getRewardScene();
    //_scene->getScenesManager()->pushScene(scene);
}

void WinMatchState::onStateExit() {
    _scene->getScenesManager()->popScene(); // popea CaromScene
    _scene->getScenesManager()->pushScene(std::make_shared<EndGameScene>(_scene->getGame(), true));

    // if(_scene->isBossMatch()) {
    //     _scene->getScenesManager()->popScene(); // ! popea PoolScene? NO, POPEA REWARD
    //     _scene->getGame()->getProgressionManager()->anteUp(); // Esto tiene que estar en reward
    //     _scene->getScenesManager()->pushScene(std::make_shared<PoolScene>(_scene->getGame())); // Nueva PoolScene
    // }
}

bool WinMatchState::checkCondition(State*& state) {
    state = new NullState(_scene);
    return true;
}