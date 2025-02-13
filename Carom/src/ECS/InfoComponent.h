#pragma once
#include "Component.h"
class Entity;

namespace ecs{
    class InfoComponent : public Component{
    public:
        InfoComponent(Entity* ent) : Component(ent) {}
        virtual ~InfoComponent(){}
    
    private:
        void init() override {}
        
        void update() override {}
        void render() override {}
        void handleEvent() override {}
    };

}