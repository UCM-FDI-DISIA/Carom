#include "WhiteBallScorerComponent.h"
#include "RigidBodyComponent.h"
#include "Entity.h"
#include "ColorBallScorerComponent.h"
#include "ScoreContainer.h"

namespace ecs{
    void WhiteBallScorerComponent::init(){
        _myEntity->getComponent<RigidBodyComponent>()->setOnCollisionEnter([this](entity_t other){

            //if is cushion
            if(false) cushions++;
            else if(other->tryGetComponent<ColorBallScorerComponent>()){
                if(!previouslyHit){
                    //scorer.add(1)
                    previouslyHit = true;
                }
                else{
                    //scorer.add(4*2^cushions);
                    cushions = 0;
                    previouslyHit = false;
                }
            }
        });
    }
}