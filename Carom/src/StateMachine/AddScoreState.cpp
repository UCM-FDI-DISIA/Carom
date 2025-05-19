#include "AddScoreState.h"
#include "HitState.h"
#include "BossState.h"
#include "WinMatchState.h"
#include "CaromScene.h"
#include "LoseMatchState.h"
#include "RigidBodyComponent.h"
#include "BallHandler.h"
#include <iostream>

AddScoreState::AddScoreState(CaromScene* scene) : State(scene)
{

}

void
AddScoreState::onStateEnter() {
    BallHandler* b;

    for (auto& e : _scene->getEntitiesOfGroup(grp::WHITEBALL)) {
        if(e->tryGetComponent<BallHandler>(b)) {
            b->onStrikeEnd();
        }
    }
    
    for (auto& e : _scene->getEntitiesOfGroup(grp::EFFECTBALLS)) {
        if(e->tryGetComponent<BallHandler>(b)) {
            b->onStrikeEnd();
        }
    }

    _scene->addPointsFromRound();
}

void
AddScoreState::onStateExit() {

}

bool
AddScoreState::checkCondition(State*& state) {

    //Elige a qué estado cambiar en función del flujo
    if(_scene->roundWins()) state = new WinMatchState(_scene);
    else if(_scene->getRemainingHits() > 0) {
        if(_scene->isBossMatch())
            state = new BossState(_scene);
        else state = new HitState(_scene);
    } 
    else state = new LoseMatchState(_scene);

    return true;
}
