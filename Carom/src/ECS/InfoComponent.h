#pragma once
#include "Component.h"
class Entity;

namespace ecs{
    class InfoComponent : public Component{
    public:
        virtual ~InfoComponent(){}
    
    private:
        void init(Entity*) override {}
        
        void update(Entity*) override {}
        void render(Entity*) override {}
        void handleEvent(Entity*) override {}
    };

}