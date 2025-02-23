#pragma once
#include "Component.h"
#include "ecs.h"

namespace ecs{

//cambiar todo esto con herencia del componente de Mika
class ColorBallScorerComponent : public ecs::Component{
    
public:
    __CMPID_DECL__(cmp::COLORBALLSCORER);
    void init() override;
    /*
        ON HIT ENTER
        if(isColorBall) ColorHitManager.checkColisions(pos de hit);
    */
};
}