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
    float _opacity = 255;

    SDL_Rect _absCenteredRect;

    // See ecs.h for layers enum
    layerId_t _defaultRenderLayer;
public:
    RenderComponent(Entity* ent, layerId_t renderLayer, SDL_Color defaultColor = {255, 255, 255, 0});
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

    void changeDefaultColorTint(int r, int g, int b);
    void changeColorTint(int r, int g, int b);
    void resetColorTint();

    inline SDL_Color getColorTint() {return _color;}

    void changeOpacity(float opacity);
    inline float* getOpacity() { return &_opacity;}

};
