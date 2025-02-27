#pragma once
#include "PhysicsComponent.h"
#include "ecs.h"

namespace ecs{


//cambiar todo esto con herencia del componente de Mika
class WhiteBallScorerComponent : PhysicsComponent{
    
    int cushions = 0; // rebotes en paredes.
    bool previouslyHit = false; // para ver si la whiteball ha tocado previamente una colorball.

public:
__CMPID_DECL__(cmp::WHITEBALLSCORER);

    // funcion q se activa al colisionar con "other".
    void onCollisionEnter(entity_t other); 

    //setea cushions a 0 y previously hit a false al comienzo del turno
    //void refreshOnNewTurn();
};
}