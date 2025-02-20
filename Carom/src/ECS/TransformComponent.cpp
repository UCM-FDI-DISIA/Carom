#include "TransformComponent.h"
#include <iostream>

namespace ecs{

    TransformComponent::TransformComponent(Entity* ent, const Vector2D& pos) 
        : InfoComponent(ent), 
        _position(pos), 
        _scale({1,1}),
        _rotation(0)
        {

        }
}