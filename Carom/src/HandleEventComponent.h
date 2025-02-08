#pragma once
#include "Component.h"
class Entity;

class HandleEventComponent : public Component
{
public:
    virtual void update(Entity* e) {}
    void render(Entity* e) {}
    void handleEvent(Entity* e) = 0;
};