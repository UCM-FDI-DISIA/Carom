#include "WhiteBallScorerComponent.h"
#include "RigidBodyComponent.h"
#include "Entity.h"
#include "ColorBallScorerComponent.h"
#include "CaromScene.h"
#include "InventoryManager.h"

#include "WallComponent.h"


#include <algorithm>
#include <iostream>

#include "CircleRBComponent.h"

WhiteBallScorerComponent::WhiteBallScorerComponent(entity_t ent): PhysicsComponent(ent), _previouslyHit(0), _cushions(0), _inventory(InventoryManager::Instance())
{ 
}
void WhiteBallScorerComponent::onCollisionEnter(entity_t other, b2Manifold& contactData){
                                                // ¿Esto está bien?
    if(other->tryGetComponent<WallComponent>() && _previouslyHit) _cushions++;
    else if(other->tryGetComponent<ColorBallScorerComponent>()){
        CaromScene* a_scene = dynamic_cast<CaromScene*>(&_myEntity->getScene());
        if(a_scene == nullptr) return;

        // muy crudo, habria que moverlo a una funcion
        b2Vec2 a_vec = other->getTransform()->getPosition() - _myEntity->getTransform()->getPosition();
        b2Vec2 a_pos = (other->getTransform()->getPosition() + _myEntity->getTransform()->getPosition()) * 0.5;
        double a_rot = (-(atan2(a_vec.y, a_vec.x) + B2_PI/2) * (180.0f / B2_PI));

        // std::cout << a_rot << "\n";

        a_scene->createFeedbackTest(a_pos, a_rot);

        if(!_previouslyHit){
            //scorer.add(1)
            a_scene->addScore(baseHitScore + _inventory->getHitEase());
            _previouslyHit = true;
        }
        else{
            //scorer.add(4*2^cushions);
            a_scene->addScore((baseCaromScore + _inventory->getCaromEase())*pow(2, _cushions));
            _cushions = 0;
            _previouslyHit = false;
        }
    }
}

void WhiteBallScorerComponent::refreshOnNewTurn(){
    _previouslyHit = false;
    _cushions = 0;
}