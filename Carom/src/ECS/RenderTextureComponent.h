#pragma once
#include "RenderComponent.h"

class Texture;
class TransformComponent;
namespace ecs {
    class RenderTextureComponent : public RenderComponent {
    private:
        Texture* _texture;
        TransformComponent* _transform;
    public:
        RenderTextureComponent(Texture*);
        ~RenderTextureComponent();
        void render(Entity*) override;
    };
}