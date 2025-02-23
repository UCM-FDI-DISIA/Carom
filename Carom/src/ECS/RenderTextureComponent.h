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

        RenderTextureComponent(Entity*, Texture*);
        ~RenderTextureComponent() {};

        void render(Camera*) override;
        void init() override;
    };
}