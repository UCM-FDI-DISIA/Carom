#include "ScoringState.h"

#include "PostScoringState.h"
// #include "EntityManager.h"
#include "CaromScene.h"
// #include "StickInputComponent.h"


void
ScoringState::onStateEnter() {
    // for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO)) {
    //     if (e->hasComponent<StickInputComponent>(e)){
    //         _scene->getComponent<StickInputComponent>(e)->disable();
    //         _scene->getComponent<RenderTextureComponent>(e)->disable();
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
    //     if(!_scene->getComponent<TransformComponent>(e).isNotMoving())
    //     return false;
    // }

    // auto effectBalls = _scene->getEntitiesOfGroup(ecs::grp::EFFECTBALLS);
    // for(auto& e : effectBalls) {
    //     if(!_scene->getComponent<TransformComponent>(e).isNotMoving())
    //     return false;
    // }

    return true;
}
