#pragma once
class Entity;

class Component
{
public:
    Component() {}
    virtual ~Component() = 0;

    virtual void update(Entity* e) = 0;
    virtual void render(Entity* e) = 0;
    virtual void handleEvent(Entity* e) = 0;
};