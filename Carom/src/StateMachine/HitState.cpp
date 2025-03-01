#include "HitState.h"
#include "CaromScene.h"
#include "StickInputComponent.h"
#include "ScoringState.h"
#include "Button.h"


HitState::HitState(ecs::CaromScene* scene) : State(scene) 
{

}

void
HitState::onStateEnter() {
    std::cout<<"Enter hit state"<<std::endl;

    for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO))
        e->activate();
}

void
HitState::onStateExit() {
    std::cout<<"Exit hit state"<<std::endl;
    for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO))
        e->deactivate();
}

bool 
HitState::checkCondition(State*& state) {
    // TODO: comprobar si la bola blanca ya ha sido golpeada
    if(_scene->getEntitiesOfGroup(ecs::grp::PALO)[0]->getComponent<ecs::StickInputComponent>()->hasShoot()){
        state = new ScoringState(_scene);
        return true;
    }
        
    return false;
}