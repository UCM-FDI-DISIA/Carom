#pragma once
#include "TutorialTwoScoringState.h"
#include "CaromScene.h"
#include "RigidBodyComponent.h"
#include "TutorialTwoHitState.h"
#include "ScenesManager.h"
#include "NullState.h"

TutorialTwoScoringState::TutorialTwoScoringState(CaromScene* scene): ScoringState(scene){

}

bool TutorialTwoScoringState::checkCondition(State*& state){
    //Comprueba que ninguna bola se mueva
    auto whiteBall = _scene->getEntitiesOfGroup(grp::WHITEBALL);
    for(auto& e : whiteBall) {
        if(_scene->getComponent<RigidBodyComponent>(e)->isMoving())
            return false;
    }

    auto effectBalls = _scene->getEntitiesOfGroup(grp::EFFECTBALLS);
    for(auto& e : effectBalls) {
        if(_scene->getComponent<RigidBodyComponent>(e)->isMoving())
            return false;
    }

    state = new TutorialTwoHitState(_scene);
        return true;
}

void TutorialTwoScoringState::onStateExit(){
    int lastPoints = _scene->getRoundScore();
    _scene->addPointsFromRound();

    if(lastPoints >=4){
        //pop a la escena de texto
        _scene->getScenesManager()->popScene();
        //pop a esta escena
        _scene->getScenesManager()->popScene();
    }
    
}