#pragma once
#include "Component.h"
class Entity;

namespace ecs{
    class InfoComponent : public Component{
    public:
        InfoComponent(Entity* e) : Component(e) {}
        virtual ~InfoComponent(){}
    
    private:
        void init(Entity*) override {}
        
        void update(Entity*) override {}
        void render(Entity*) override {}
        void handleEvent(Entity*) override {}
    };

}