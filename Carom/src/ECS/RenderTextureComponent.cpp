#include "RenderTextureComponent.h"
#include "Texture.h"

namespace ecs{
    RenderTextureComponent::RenderTextureComponent(Texture* texture) : RenderComponent(), _texture(texture), _transform(nullptr)
    {

    }

    void RenderTextureComponent::render(Entity* entity) {
        if(_transform = nullptr) {
            
        }
        _texture->render(1, 1);
    }
}