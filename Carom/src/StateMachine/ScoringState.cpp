#include "ScoringState.h"
#include "PostScoringState.h"

#include "CaromScene.h"
// #include "StickInputComponent.h"
#include "RigidBodyComponent.h"


void
ScoringState::onStateEnter() {
    // for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO)) {
    //     if (_scene->hasComponent<StickInputComponent>(e)){
    //         e->disable();
    //     }
    // }
}

void
ScoringState::onStateExit() {
    _scene->setNewState(new PostScoringState(_scene));
}

bool
ScoringState::checkCondition(State*& state) {
    // TODO: comprobar si todas las bolas han dejado de moverse
    // auto whiteBall = _scene->getEntitiesOfGroup(ecs::grp::WHITEBALL);
    // for(auto& e : whiteBall) {
    //     if(!_scene->getComponent<RigidBodyComponent>(e).isNotMoving())
    //     return false;
    // }

    // auto effectBalls = _scene->getEntitiesOfGroup(ecs::grp::EFFECTBALLS);
    // for(auto& e : effectBalls) {
    //     if(!_scene->getComponent<RigidBodyComponent>(e).isNotMoving())
    //     return false;
    // }

    return true;
}
