#include "ScoringState.h"
#include "HitState.h"
#include "WinMatchState.h"
#include "CaromScene.h"
#include "LoseMatchState.h"
#include "RigidBodyComponent.h"
#include "StickInputComponent.h"


ScoringState::ScoringState(ecs::CaromScene* scene) : State(scene)
{
}

void
ScoringState::onStateEnter() {
    // std::cout<< "enter scoring state" << std::endl;

}

void
ScoringState::onStateExit() {
//  std::cout<< "exit scoring state" << std::endl;
    
}

bool
ScoringState::checkCondition(State*& state) {
    // std::cout<< "scoring State Checking condition" << std::endl;

    //Comprueba que ninguna bola se mueva
    auto whiteBall = _scene->getEntitiesOfGroup(ecs::grp::WHITEBALL);
    for(auto& e : whiteBall) {
        if(_scene->getComponent<ecs::RigidBodyComponent>(e)->isMoving()){
            return false;
        }
    }

    auto effectBalls = _scene->getEntitiesOfGroup(ecs::grp::EFFECTBALLS);
    for(auto& e : effectBalls) {
        if(_scene->getComponent<ecs::RigidBodyComponent>(e)->isMoving())
            return false;
    }

    //Elige a qué estado cambiar en función del flujo (falta el getScoreContainer)
    if(_scene->getCurrentScore() >= _scene->getScoreToBeat()) 
        state = new WinMatchState(_scene);
    else if(_scene->getRemainingHits() > 0) 
        state = new HitState(_scene);
    else 
        state = new LoseMatchState(_scene);

    return true;
}
