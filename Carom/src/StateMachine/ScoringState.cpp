#include "ScoringState.h"
#include "HitState.h"
#include "WinMatchState.h"

#include "CaromScene.h"
// #include "StickInputComponent.h"
#include "RigidBodyComponent.h"

ScoringState::ScoringState(CaromScene* scene) : State(scene)
{

}

void
ScoringState::onStateEnter() {
    // for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO)) 
    //      e->disable();
}

void
ScoringState::onStateExit() {
    
}

bool
ScoringState::checkCondition(State*& state) {
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

    // if(_scene->getScoreContainer()->roundWins()) state = new WinMatchState(_scene);
    // else if(_scene->getRemainingHits() > 0) state = new HitState(_scene);
    // else state = new LoseState(_scene);

    return true;
}
