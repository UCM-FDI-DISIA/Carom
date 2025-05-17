#include "HitState.h"
#include "ScoringState.h"
#include "CaromScene.h"
#include "StickInputComponent.h"
#include "RenderTextureComponent.h"
#include "Button.h"
#include "WhiteBallScorerComponent.h"
#include <iostream>
#include "BallHandler.h"


HitState::HitState(CaromScene* scene) : State(scene) 
{

}

void
HitState::onStateEnter() {
    #ifdef _DEBUG
        std::cout<< "Enter HIT state" << std::endl;
    #endif
    
    auto whiteBall = _scene->getEntitiesOfGroup(grp::WHITEBALL);
    assert(whiteBall.size() > 0);

    setBallInputActive(true);

    whiteBall[0]->getComponent<WhiteBallScorerComponent>()->refreshOnNewTurn();
}

void
HitState::onStateExit() {
    setBallInputActive(false);
    setStickActive(false);
    setAimLineActive(false);
}

bool 
HitState::checkCondition(State*& state) {
    #ifdef _DEBUG
        std::cout << "checkCondition hitState" <<std::endl;
    #endif
    
    for (auto& e : _scene->getEntitiesOfGroup(grp::PALO)) { 
        if(e->tryGetComponent<StickInputComponent>() && e->getComponent<StickInputComponent>()->hasShot()) {
            #ifdef _DEBUG
                std::cout << "Cambio a Scoring\n";
            #endif
            
            state = new ScoringState(_scene);
            return true;
        }
    }

    return false;
}