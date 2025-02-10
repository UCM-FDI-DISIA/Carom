#include "RenderTextureComponent.h"
#include "Texture.h"
#include "Entity.h"
#include "TransformComponent.h"

namespace ecs {
    RenderTextureComponent::RenderTextureComponent(Texture* texture) : RenderComponent(), _texture(texture), _transform(nullptr)
    {

    }

    void RenderTextureComponent::init(Entity* entity){
        _transform = entity->getComponent<TransformComponent>(TRANSFORM);
    }

    void RenderTextureComponent::render(Entity* entity) {
        _texture->render(_transform->getPosition()->getX(), _transform->getPosition()->getY());
    }
}