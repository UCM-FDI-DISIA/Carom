#pragma once
#include "Component.h"

//cambiar todo esto con herencia del componente de Mika
class WhiteBallScorerComponent : ecs::Component{
    int cushions = 0;
    bool previouslyHit = false;
};