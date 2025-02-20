#pragma once
#include "ecs.h"
#include "RenderComponent.h"

class Texture;

namespace ecs {
    class TransformComponent;
    
    class RenderTextureComponent : public RenderComponent {
    private:
        Texture* _texture;
        TransformComponent* _transform;
    public:
        __CMPID_DECL__(cmp::RENDER_TEXTURE);

        // The lower the further (for example: 0 = Background, 1 = Foreground)
        // Mesa: suelo = 0, marco = 1, sombra marco = 2
        int renderOrder;

        RenderTextureComponent(Entity*, Texture*, int renderOrder);
        ~RenderTextureComponent() {};

        void render() override;
        void init() override;
    };
}