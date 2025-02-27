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
            if(_myEntity->tryGetComponent<WallComponent>()){ // si choca con una pared, aumenta cushions.
                cushions++;
            }
            else if(other->tryGetComponent<ColorBallScorerComponent>()){ // si colisiona con una bola de color.
                CaromScene* a_scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());
                if(a_scene != nullptr){
                    // si no ha habido un golpe previo.
                    if(!previouslyHit){
                        //scorer.add(1)
                        a_scene->getScoreContainer()->addScore(1);
                        previouslyHit = true;
                    }
                    // si ha colisionado con una bola de color y ha habido golpe previo con otra bola de color
                    else{
                        //scorer.add(4*2^cushions);
                        a_scene->getScoreContainer()->addScore(4 * pow(2, cushions)); // carambola y reiniciamos.
                        cushions = 0;
                        previouslyHit = false;
                    }
                }
                
            }
    }
}