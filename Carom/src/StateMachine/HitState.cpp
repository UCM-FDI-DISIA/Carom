#include "HitState.h"
#include "ScoringState.h"
#include "CaromScene.h"
#include "StickInputComponent.h"
#include "RenderTextureComponent.h"
#include "Button.h"
#include "WhiteBallScorerComponent.h"
#include <iostream>


HitState::HitState(CaromScene* scene) : State(scene) 
{

}

void
HitState::onStateEnter() {
    for (auto& e : _scene->getEntitiesOfGroup(grp::WHITEBALL)) {
        if(e->tryGetComponent<Button>()) {
            e->getComponent<Button>()->setEnabled(true);
        }
    }

    _scene->getEntitiesOfGroup(grp::WHITEBALL)[0]->getComponent<WhiteBallScorerComponent>()->refreshOnNewTurn();
}

void
HitState::onStateExit() {
    for (auto& e : _scene->getEntitiesOfGroup(grp::PALO)) {
        std::cout << "Saliendo de Hit\n";
        e->deactivate();
    }
    for (auto& e : _scene->getEntitiesOfGroup(grp::WHITEBALL)) {
        if(e->tryGetComponent<Button>()) {
            e->getComponent<Button>()->setEnabled(false);
        }
    }
}

bool 
HitState::checkCondition(State*& state) {
    // TODO: comprobar si la bola blanca ya ha sido golpeada ARQUITECTURA MIRAR SI ESTO ESTÁ BIEN
    for (auto& e : _scene->getEntitiesOfGroup(grp::PALO)){
        if(e->tryGetComponent<StickInputComponent>() && e->getComponent<StickInputComponent>()->hasShot()) {
            std::cout << "Cambio a Scoring\n";
            state = new ScoringState(_scene);
            return true;
        }
    }

    return false;
}