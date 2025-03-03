#include "HitState.h"
#include "CaromScene.h"
#include "StickInputComponent.h"
#include "RenderTextureComponent.h"
#include "Button.h"


HitState::HitState(ecs::CaromScene* scene) : State(scene) 
{

}

void
HitState::onStateEnter() {
    for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO)) {
        // e->activate();
        if(e->tryGetComponent<ecs::Button>()) {
            e->getComponent<ecs::Button>()->setEnabled(true);
        }
    }
}

void
HitState::onStateExit() {
    for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO)) {
        // e->deactivate();
        if(e->tryGetComponent<ecs::Button>()) {
            e->getComponent<ecs::Button>()->setEnabled(false);
        }
    }
}

bool 
HitState::checkCondition(State*& state) {
    // TODO: comprobar si la bola blanca ya ha sido golpeada ARQUITECTURA MIRAR SI ESTO ESTÁ BIEN
    for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO)){
        if(e->tryGetComponent<ecs::StickInputComponent>() && e->getComponent<ecs::StickInputComponent>()->hasShot())
            return true;
    }

    return false;
}