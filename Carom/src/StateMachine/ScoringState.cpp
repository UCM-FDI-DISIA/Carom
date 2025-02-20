#include "ScoringState.h"

#include "PostScoringState.h"
// #include "EntityManager.h"
#include "CaromScene.h"
// #include "StickInputComponent.h"


void
ScoringState::onStateEnter() {
    // for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO)) {
    //     if (_scene->hasComponent<StickInputComponent>(e)){
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
    return true;
}
