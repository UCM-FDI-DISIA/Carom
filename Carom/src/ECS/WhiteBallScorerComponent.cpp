#include "WhiteBallScorerComponent.h"
#include "RigidBodyComponent.h"
#include "Entity.h"
#include "ColorBallScorerComponent.h"
#include "CaromScene.h"
#include "WallComponent.h"
#include <algorithm>

WhiteBallScorerComponent::WhiteBallScorerComponent(entity_t ent): PhysicsComponent(ent), _previouslyHit(0), _cushions(0)
{
    
}
void WhiteBallScorerComponent::onCollisionEnter(entity_t other){

    if(other->tryGetComponent<WallComponent>() && _previouslyHit) _cushions++;
    else if(other->tryGetComponent<ColorBallScorerComponent>()){
        CaromScene* a_scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());
        if(a_scene == nullptr) return;

        if(!_previouslyHit){
            //scorer.add(1)
            a_scene->addScore(1);
            _previouslyHit = true;
        }
        else{
            //scorer.add(4*2^cushions);
            a_scene->addScore(4*pow(2, _cushions));
            _cushions = 0;
            _previouslyHit = false;
        }

    }
}

void WhiteBallScorerComponent::refreshOnNewTurn(){
    _previouslyHit = false;
    _cushions = 0;
}