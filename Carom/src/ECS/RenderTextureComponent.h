#pragma once
#include "ecs.h"
#include "RenderComponent.h"
#include "ITransform.h"

class SDL_Rect;
class Texture;
class SDL_Color;

namespace ecs {
    
    class RenderTextureComponent : public RenderComponent {
    protected:
        Texture* _texture;
        ITransform* _transform;
        float _scale; // scale de la textura (no su physical body)
    public:
        __CMPID_DECL__(cmp::RENDER_TEXTURE);

        // The lower the further (for example: 0 = Background, 1 = Foreground)
        // Mesa: suelo = 0, sombra marco = 1, marco = 2
        int renderOrder;

        RenderTextureComponent(Entity*, Texture*, int renderOrder, float scale);
        RenderTextureComponent(Entity*, Texture*, int renderOrder, float scale, SDL_Color tint);
        ~RenderTextureComponent() {};

        void render(Camera*) override;
        void init() override;
        Texture* getTexture() {return _texture;};
        virtual SDL_Rect getRect() const;

        void changeColorTint(int r, int g, int b);
        void resetColorTint();
    };
}