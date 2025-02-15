#pragma once
#include "ecs.h"
#include "RenderComponent.h"

class Texture;
class TransformComponent;
namespace ecs {
    class RenderTextureComponent : public RenderComponent {
    private:
        Texture* _texture;
        TransformComponent* _transform;
    public:
        __CMPID_DECL__(cmp::RENDER_TEXTURE);

        RenderTextureComponent(Entity*, Texture*);
        ~RenderTextureComponent() {};

        void render() override;
        void init() override;
    };
}