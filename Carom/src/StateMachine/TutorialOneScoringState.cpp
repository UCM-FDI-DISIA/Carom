#pragma once
#include "TutorialOneScoringState.h"
#include "CaromScene.h"
#include "RigidBodyComponent.h"
#include "TutorialOneHitState.h"
#include "ScenesManager.h"

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

    //UNA VEZ QUE NO SE MUEVAN:
    if(_scene->getCurrentScore()>0 || _scene->getRoundScore()>0){
        _scene->getScenesManager()->popScene();
    }

    state = new TutorialOneHitState(_scene);
        return true;
}