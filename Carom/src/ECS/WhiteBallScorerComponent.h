#pragma once
#include "Component.h"
#include "ecs.h"

namespace ecs{


//cambiar todo esto con herencia del componente de Mika
class WhiteBallScorerComponent : ecs::Component{
    
    int cushions = 0;
    bool previouslyHit = false;

public:
__CMPID_DECL__(cmp::WHITEBALLSCORER);
    void init() override;
    //setea cushions a 0 y previously hit a false al comienzo del turno
    void refreshOnNewTurn();
};
}