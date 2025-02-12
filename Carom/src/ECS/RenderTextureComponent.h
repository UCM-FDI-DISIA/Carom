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
        RenderTextureComponent(Entity*, Texture*);
        ~RenderTextureComponent();

        void render() override;
        void init() override;
    };
}