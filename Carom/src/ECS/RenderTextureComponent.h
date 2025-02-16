#pragma once
#include "RenderComponent.h"

namespace ecs {
class Texture;
class TransformComponent;
    class RenderTextureComponent : public RenderComponent {
    private:
        Texture* _texture;
        TransformComponent* _transform;
    public:
        RenderTextureComponent(Entity*, Texture*);
        ~RenderTextureComponent();

        void render() override;
        void init() override;
    };
}