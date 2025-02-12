#include "TransformComponent.h"

using namespace ecs;

TransformComponent::TransformComponent(Entity* ent) : InfoComponent(ent), _position(Vector2D(0, 0)),
                                                      _scale({1,1}), _rotation(0) 
{
    
}