#pragma once
#include "ecs.h"
#include "RenderComponent.h"
#include "ITransform.h"
#include "SDL.h"

class SDL_Rect;
class Texture;

namespace ecs {
    
    class RenderTextureComponent : public RenderComponent {
    protected:
        Texture* _texture;
        ITransform* _transform;
        float _scale; // scale de la textura (no su physical body)
        bool _isPortion = false; // If the rect is a portion of a rect

        SDL_Color _color = {255,255,255,0};

        // See ecs.h for layers enum
        ecs::layerId_t _defaultRenderLayer;
        ecs::layerId_t _renderLayer;
    public:
        __CMPID_DECL__(cmp::RENDER_TEXTURE);


        RenderTextureComponent(Entity*, Texture*, int renderLayer, float scale);
        RenderTextureComponent(Entity*, Texture*, int renderLayer, float scale, SDL_Color tint);
        ~RenderTextureComponent() {};

        void render() override;
        void init() override;
        Texture* getTexture() {return _texture;};
        virtual SDL_Rect getRect() const;
        inline void setPortion(bool isPortion) {_isPortion = isPortion;}

        ecs::layerId_t getRenderLayer() { return _renderLayer; }
        void setRenderLayer(ecs::layerId_t layer);
        // To go deeper/down n layers
        void nDownRenderLayer(int n) { _renderLayer -= n; }
        // To came closer/up n layers
        void nUpRenderLayer(int n) { _renderLayer += n; }
        void resetRenderLayer();

        void changeColorTint(int r, int g, int b);
        void resetColorTint();
    };
}