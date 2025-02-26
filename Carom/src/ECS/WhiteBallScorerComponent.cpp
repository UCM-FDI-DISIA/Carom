#include "WhiteBallScorerComponent.h"
#include "RigidBodyComponent.h"
#include "Entity.h"
#include "ColorBallScorerComponent.h"
#include "ScoreContainer.h"
#include "CaromScene.h"
#include "WallComponent.h"
#include <algorithm>

namespace ecs{
    void WhiteBallScorerComponent::onCollisionEnter(entity_t other){

            //if is cushion
            if(_myEntity->tryGetComponent<WallComponent>()) cushions++;
            else if(other->tryGetComponent<ColorBallScorerComponent>()){
                CaromScene* a_scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());
                if(a_scene != nullptr){
                    if(!previouslyHit){
                        //scorer.add(1)
                        a_scene->getScoreContainer()->addScore(1);
                        previouslyHit = true;
                    }
                    else{
                        //scorer.add(4*2^cushions);
                        a_scene->getScoreContainer()->addScore(4*pow(2, cushions));
                        cushions = 0;
                        previouslyHit = false;
                    }
                }
                
            }
    }
}