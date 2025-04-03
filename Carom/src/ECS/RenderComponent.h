#pragma once
#include "Component.h"
class Entity;
struct SDL_Rect;

class RenderComponent : public Component
{
public:
    RenderComponent(Entity* ent) : Component(ent) {}
    virtual ~RenderComponent(){}

    void update() override {}
    void handleEvent() override {}

    virtual SDL_Rect getRenderRect() const = 0;
};
