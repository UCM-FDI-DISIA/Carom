#include "HitState.h"
#include "ScoringState.h"
#include "CaromScene.h"
#include "StickInputComponent.h"
#include "RenderTextureComponent.h"
#include "Button.h"
#include "WhiteBallScorerComponent.h"
#include <iostream>


HitState::HitState(ecs::CaromScene* scene) : State(scene) 
{

}

void
HitState::onStateEnter() {
    for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::WHITEBALL)) {
        if(e->tryGetComponent<ecs::Button>()) {
            e->getComponent<ecs::Button>()->setEnabled(true);
        }
    }

    _scene->getEntitiesOfGroup(ecs::grp::WHITEBALL)[0]->getComponent<ecs::WhiteBallScorerComponent>()->refreshOnNewTurn();
}

void
HitState::onStateExit() {
    for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO)) {
        std::cout << "Saliendo de Hit\n";
        e->deactivate();
    }
    for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::WHITEBALL)) {
        if(e->tryGetComponent<ecs::Button>()) {
            e->getComponent<ecs::Button>()->setEnabled(false);
        }
    }
}

bool 
HitState::checkCondition(State*& state) {
    for (auto& e : _scene->getEntitiesOfGroup(ecs::grp::PALO)){
        if(e->tryGetComponent<ecs::StickInputComponent>() && e->getComponent<ecs::StickInputComponent>()->hasShot()) {
            std::cout << "Cambio a Scoring\n";
            state = new ScoringState(_scene);
            return true;
        }
    }

    return false;
}