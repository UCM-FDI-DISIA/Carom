#include "LoseMatchState.h"
#include "CaromScene.h"
#include "ScenesManager.h"
#include "NullState.h"
#include "GameScene.h"
#include "EndGameScene.h"


LoseMatchState::LoseMatchState(CaromScene* scene) : State(scene)
{
}

void LoseMatchState::onStateEnter() 
{
}

void LoseMatchState::onStateExit() {
    _scene->getScenesManager()->popScene(); // popea CaromScene
    _scene->getScenesManager()->pushScene(std::make_shared<EndGameScene>(_scene->getGame(), false, _scene->isBossMatch()));
}

bool LoseMatchState::checkCondition(State*& state) 
{    
    state = new NullState(_scene);
    return true;
}