/*#include "RenderTextureComponent.h"
#include "Texture.h"
#include "Entity.h"
#include "TransformComponent.h"

namespace ecs {
    RenderTextureComponent::RenderTextureComponent(Entity* ent, Texture* texture) : RenderComponent(ent), _texture(texture), _transform(nullptr)
    {

    }

    void RenderTextureComponent::init(){
        _transform = _myEntity->getComponent<TransformComponent>(TRANSFORM);
    }

    void RenderTextureComponent::render() {
        _texture->render(_transform->getPosition()->getX(), _transform->getPosition()->getY());
    }
}*/