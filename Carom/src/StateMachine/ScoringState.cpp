#include "ScoringState.h"
#include "HitState.h"
#include "BossState.h"
#include "WinMatchState.h"
#include "CaromScene.h"
#include "LoseMatchState.h"
#include "RigidBodyComponent.h"
#include "BallHandler.h"
#include <iostream>

ScoringState::ScoringState(CaromScene* scene) : State(scene)
{

}

void
ScoringState::onStateEnter() {
    std::cout << "Entrando en Scoring\n";
    _scene->decrementRemainingHits();

    #ifdef _DEBUG
        _scene->setCanFastForward(true);
    #endif
}

void
ScoringState::onStateExit() {
    for (auto& e : _scene->getEntitiesOfGroup(grp::WHITEBALL)) {
        if(e->tryGetComponent<BallHandler>()) {
            e->getComponent<BallHandler>()->onStrikeEnd();
        }
    }
    
    for (auto& e : _scene->getEntitiesOfGroup(grp::EFFECTBALLS)) {
        if(e->tryGetComponent<BallHandler>()) {
            e->getComponent<BallHandler>()->onStrikeEnd();
        }
    }

    _scene->addPointsFromRound();
    
    #ifdef _DEBUG
        _scene->setCanFastForward(false);
    #endif
}

bool
ScoringState::checkCondition(State*& state) {
    // std::cout << "checkCondition ScoringState" << std::endl;
    //Comprueba que ninguna bola se mueva
    auto whiteBall = _scene->getEntitiesOfGroup(grp::WHITEBALL);
    for(auto& e : whiteBall) {
        if(_scene->getComponent<RigidBodyComponent>(e)->isMoving())
            return false;
    }

    auto effectBalls = _scene->getEntitiesOfGroup(grp::EFFECTBALLS);
    for(auto& e : effectBalls) {
        if(_scene->getComponent<RigidBodyComponent>(e)->isMoving())
            return false;
    }

    //Elige a qué estado cambiar en función del flujo (falta el getScoreContainer)
    if(_scene->roundWins()) state = new WinMatchState(_scene);
    else if(_scene->getRemainingHits() > 0) {
        if(_scene->isBossMatch())
            state = new BossState(_scene);
        else state = new HitState(_scene);
    } 
    else state = new LoseMatchState(_scene);

    return true;
}
