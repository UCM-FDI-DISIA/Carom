#pragma once
#include "ecs.h"
#include "RenderComponent.h"
#include "ITransform.h"

class Texture;

namespace ecs {
    
    class RenderTextureComponent : public RenderComponent {
    private:
        Texture* _texture;
        ITransform* _transform;
    public:
        __CMPID_DECL__(cmp::RENDER_TEXTURE);

        // The lower the further (for example: 0 = Background, 1 = Foreground)
        // Mesa: suelo = 0, marco = 1, sombra marco = 2
        int renderOrder;

        RenderTextureComponent(Entity*, Texture*, int renderOrder);
        ~RenderTextureComponent() {};

        void render(Camera*) override;
        void init() override;
    };
}