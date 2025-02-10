#include "RenderTextureComponent.h"
#include "Texture.h"
#include "Entity.h"
#include "TransformComponent.h"

namespace ecs{
    RenderTextureComponent::RenderTextureComponent(Texture* texture) : RenderComponent(), _texture(texture), _transform(nullptr)
    {

    }

    void RenderTextureComponent::render(Entity* entity) {
        if(_transform = nullptr) entity->tryGetComponent(ecs::TRANSFORM, _transform);
        _texture->render(_transform->getPosition()->getX(), transform->getPosition()->getY());
    }
}