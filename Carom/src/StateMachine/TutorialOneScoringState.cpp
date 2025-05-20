#pragma once
#include "TutorialOneScoringState.h"
#include "CaromScene.h"
#include "RigidBodyComponent.h"
#include "TutorialOneHitState.h"
#include "ScenesManager.h"
#include "NullState.h"

TutorialOneScoringState::TutorialOneScoringState(CaromScene* scene): ScoringState(scene){

}

bool TutorialOneScoringState::checkCondition(State*& state){
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

    state = new TutorialOneHitState(_scene);
        return true;
}

void TutorialOneScoringState::onStateExit(){
    _scene->addPointsFromRound();
    if(_scene->getCurrentScore() + _scene->getRoundScore()>=_scene->getScoreToBeat()){
        //pop a la escena de texto
        _scene->getScenesManager()->popScene();
        //pop a esta escena
        _scene->getScenesManager()->popScene();
    }
    
}