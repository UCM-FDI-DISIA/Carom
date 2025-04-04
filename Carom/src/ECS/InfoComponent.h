#pragma once
#include "Component.h"
class Entity;

class InfoComponent : public Component{
public:
    InfoComponent(Entity* ent) : Component(ent) {}
    virtual ~InfoComponent(){}

private:
    void init() override {}
    
    virtual void update() override {}
    void render() override {}
    void handleEvent() override {}
};
