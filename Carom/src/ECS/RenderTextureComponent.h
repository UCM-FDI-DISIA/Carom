#pragma once

#include "ecs.h"
#include "RenderComponent.h"
#include "ITransform.h"
#include "SDL.h"

class SDL_Rect;
class Texture;

class TweenComponent;
    
class RenderTextureComponent : public RenderComponent {
    friend TweenComponent;
protected:
    Texture* _texture = nullptr;
    ITransform* _transform;
    float _scale; // scale de la textura (no su physical body)
    bool _isPortion = false; // If the rect is a portion of a rect

    SDL_Rect _absCenteredRect;

    // See ecs.h for layers enum
    layerId_t _defaultRenderLayer;
public:
    __CMPID_DECL__(cmp::RENDER_TEXTURE);


    RenderTextureComponent(Entity*, Texture*, int renderLayer, float scale);
    RenderTextureComponent(Entity*, Texture*, int renderLayer, float scale, SDL_Rect absCenteredRect);
    RenderTextureComponent(Entity*, Texture*, int renderLayer, float scale, SDL_Color tint);
    ~RenderTextureComponent() {};

    virtual void render() override;
    void init() override;
    Texture* getTexture() {return _texture;};
    void setTexture(Texture* tex);

    inline float getScale(){return _scale;}
    inline void setScale(float s) {_scale = s;}
    
    SDL_Rect getRenderRect() const override;
    float getRenderWidth();
    void setNewWidth(float newWidth);
};