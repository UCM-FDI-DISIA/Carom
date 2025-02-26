#pragma once
#include "PhysicsComponent.h"
#include "ecs.h"

namespace ecs{

//cambiar todo esto con herencia del componente de Mika
class ColorBallScorerComponent : public PhysicsComponent{
    
public:
    __CMPID_DECL__(cmp::COLORBALLSCORER);
    void onCollisionEnter(entity_t ent) override;
    /*
        ON HIT ENTER
        if(isColorBall) ColorHitManager.checkColisions(pos de hit);
    */
};
}