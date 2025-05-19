#include "ScoringState.h"
#include "AddScoreState.h"
#include "CaromScene.h"
#include "RigidBodyComponent.h"
#include <iostream>

ScoringState::ScoringState(CaromScene* scene) : State(scene)
{

}

void
ScoringState::onStateEnter() {
    
    _scene->decrementRemainingHits();
    
    #ifdef _DEBUG
        std::cout << "Entrando en Scoring\n";
        _scene->setCanFastForward(true);
    #endif
}

void
ScoringState::onStateExit() {
    
    #ifdef _DEBUG
        _scene->setCanFastForward(false);
    #endif
}

bool
ScoringState::checkCondition(State*& state) {
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
    state = new AddScoreState(_scene);

    return true;
}
