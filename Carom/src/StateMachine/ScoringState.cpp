#include "ScoringState.h"
#include "HitState.h"
#include "BossState.h"
#include "WinMatchState.h"
#include "CaromScene.h"
#include "LoseMatchState.h"
#include "RigidBodyComponent.h"
#include <iostream>

ScoringState::ScoringState(ecs::CaromScene* scene) : State(scene)
{

}

void
ScoringState::onStateEnter() {
    std::cout << "Entrando en Scoring\n";
    _scene->setCanFastForward(true);
}

void
ScoringState::onStateExit() {
    // std::cout<< "Exit scoring state" << std::endl;
    _scene->setCanFastForward(false);
}

bool
ScoringState::checkCondition(State*& state) {
    
    //Comprueba que ninguna bola se mueva
    auto whiteBall = _scene->getEntitiesOfGroup(ecs::grp::WHITEBALL);
    for(auto& e : whiteBall) {
        if(_scene->getComponent<ecs::RigidBodyComponent>(e)->isMoving())
            return false;
    }

    auto effectBalls = _scene->getEntitiesOfGroup(ecs::grp::EFFECTBALLS);
    for(auto& e : effectBalls) {
        if(_scene->getComponent<ecs::RigidBodyComponent>(e)->isMoving())
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
