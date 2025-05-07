#pragma once

#include "Component.h"
#include "SDL.h"

class Entity;
struct SDL_Rect;

class RenderComponent : public Component {
protected:
    layerId_t _renderLayer;

    SDL_Color _defaultColor;
    SDL_Color _color = {255,255,255,0};

    SDL_Rect _absCenteredRect;

    // See ecs.h for layers enum
    layerId_t _defaultRenderLayer;
public:
    RenderComponent(Entity* ent, layerId_t renderLayer);
    virtual ~RenderComponent(){}

    void update() override {}
    void handleEvent() override {}

    virtual SDL_Rect getRenderRect() const = 0;
    inline layerId_t getRenderLayer() { return _renderLayer; }
    void setRenderLayer(layerId_t layer);

    // To go deeper/down n layers
    void nDownRenderLayer(int n) { _renderLayer -= n; }
    // To come closer/up n layers
    void nUpRenderLayer(int n) { _renderLayer += n; }
    void resetRenderLayer();

    void changeColorTint(int r, int g, int b);
    void resetColorTint();
};
