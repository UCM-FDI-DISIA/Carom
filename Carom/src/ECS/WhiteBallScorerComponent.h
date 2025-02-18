#pragma once
#include "Component.h"

//cambiar todo esto con herencia del componente de Mika
class WhiteBallScorerComponent : ecs::Component{
    int cushions = 0;
    bool previouslyHit = false;

    /*
    ON HIT ENTER

    if (isCushion) cushions++
    else if (isBall) {
        if(!previouslyHit) {
            scorer.add(1);
            previouslyHit = true;
            }
        else{
            scorer.add(4*2^cushions);
            cushions =0;
            previouslyHit = false;
            }
    */

    //setea cushions a 0 y previously hit a false al comienzo del turno
    void refreshOnNewTurn();
};