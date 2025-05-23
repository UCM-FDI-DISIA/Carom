#pragma once
#include "PhysicsComponent.h"
#include "ecs.h"


//cambiar todo esto con herencia del componente de Mika
class ColorBallScorerComponent : public PhysicsComponent{
    
public:
    __CMPID_DECL__(cmp::COLORBALLSCORER);
    ColorBallScorerComponent(entity_t ent);
    
    // se activa al entrar en colision una bola de color con ent. Notifica a ColorHitManager de la colision
    void onCollisionEnter(entity_t ent, b2Manifold& contactData) override;

    /*
        ON HIT ENTER
        if(isColorBall) ColorHitManager.checkColisions(pos de hit);
    */
};