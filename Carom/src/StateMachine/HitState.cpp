#include "HitState.h"
#include "CaromScene.h"
HitState::HitState(ecs::CaromScene* scene) : State(scene) 
{

}

void
HitState::onStateEnter() {
    for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO))
        e->enable();
}

void
HitState::onStateExit() {
    for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO))
        e->disable();
}

bool 
HitState::checkCondition(State*& state) {
    // TODO: comprobar si la bola blanca ya ha sido golpeada
    return false;
}