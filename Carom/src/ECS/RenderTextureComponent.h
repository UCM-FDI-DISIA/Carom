#pragma once
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

        RenderTextureComponent(Entity* ent, Texture* texture);
        ~RenderTextureComponent() {}; // TODO: delete tex?

        void render() override;
        void init() override;
    };
}