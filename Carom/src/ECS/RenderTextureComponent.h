#pragma once

#include "ecs.h"
#include "RenderComponent.h"
#include "ITransform.h"
#include "SDL.h"

class SDL_Rect;
class Texture;
    
class RenderTextureComponent : public RenderComponent {
protected:
    Texture* _texture = nullptr;
    ITransform* _transform;
    float _scale; // scale de la textura (no su physical body)
    bool _isPortion = false; // If the rect is a portion of a rect

    SDL_Color _defaultColor;
    SDL_Color _color = {255,255,255,0};

    SDL_Rect _absCenteredRect;

    // See ecs.h for layers enum
    layerId_t _defaultRenderLayer;
public:
    __CMPID_DECL__(cmp::RENDER_TEXTURE);


    RenderTextureComponent(Entity*, Texture*, int renderLayer, float scale);
    RenderTextureComponent(Entity*, Texture*, int renderLayer, float scale, SDL_Rect absCenteredRect);
    RenderTextureComponent(Entity*, Texture*, int renderLayer, float scale, SDL_Color tint);
    ~RenderTextureComponent() {};

    void render() override;
    void init() override;
    Texture* getTexture() {return _texture;};
    void setTexture(Texture* tex);

    void setRenderLayer(layerId_t layer);
    // To go deeper/down n layers
    void nDownRenderLayer(int n) { _renderLayer -= n; }
    // To come closer/up n layers
    void nUpRenderLayer(int n) { _renderLayer += n; }
    void resetRenderLayer();

    void changeColorTint(int r, int g, int b);
    void resetColorTint();

    inline int getRenderLayer() {return _renderLayer; };

    inline float getScale(){return _scale;}
    inline void setScale(float s) {_scale = s;}

    SDL_Rect getRenderRect() const override;
};