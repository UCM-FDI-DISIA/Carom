#pragma once
#include "PhysicsComponent.h"
#include "ecs.h"

namespace ecs{


//cambiar todo esto con herencia del componente de Mika
class WhiteBallScorerComponent : PhysicsComponent{
    
    int cushions = 0;
    bool previouslyHit = false;

public:
__CMPID_DECL__(cmp::WHITEBALLSCORER);
    WhiteBallScorerComponent(entity_t ent);
    void onCollisionEnter(entity_t other);
    //setea cushions a 0 y previously hit a false al comienzo del turno
    void refreshOnNewTurn();
};
}