#include "TransformComponent.h"
#include <iostream>

namespace ecs{

    TransformComponent::TransformComponent(Entity* ent, const b2Vec2& pos) 
        : InfoComponent(ent), 
        _position(pos), 
        _scale({1,1}),
        _rotation(0)
        {

        }
}