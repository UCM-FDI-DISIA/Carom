#include "HitState.h"

// #include "StickInputComponent.h"
#include "CaromScene.h"
HitState::HitState(CaromScene* scene) : State(scene) 
{

}

void
HitState::onStateEnter() {
    // for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO)) {
    //     if (e->tryGetComponent<StickInputComponent>()){
    //         e->enable();
    //     }
    // }
}

void
HitState::onStateExit() {
    // for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO)) {
    //     if (e->tryGetComponent<StickInputComponent>()){
    //         e->disable();
    //     }
    // }
}

bool 
HitState::checkCondition(State*& state) {
    // TODO: comprobar si la bola blanca ya ha sido golpeada
    return false;
}