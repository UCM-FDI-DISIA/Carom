#pragma once

#include "Component.h"

class Entity;
struct SDL_Rect;

class RenderComponent : public Component {
protected:
    layerId_t _renderLayer;
public:
    RenderComponent(Entity* ent, layerId_t renderLayer) : Component(ent), _renderLayer(renderLayer) {}
    virtual ~RenderComponent(){}

    void update() override {}
    void handleEvent() override {}

    virtual SDL_Rect getRenderRect() const = 0;
    inline layerId_t getRenderLayer() { return _renderLayer; }
};
