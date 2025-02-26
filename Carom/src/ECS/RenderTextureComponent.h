#pragma once
#include "ecs.h"
#include "RenderComponent.h"
class SDL_Rect;
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

        void render() override;
        void init() override;
        Texture* getTexture() {return _texture;};
        SDL_Rect getRect();
    };
}