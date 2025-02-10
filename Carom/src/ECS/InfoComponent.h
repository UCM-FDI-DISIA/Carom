#pragma once
#include "Component.h"
class Entity;

namespace ecs{
    class InfoComponent : public Component{
    public:
        virtual ~InfoComponent(){}
    
    private:
        void update(Entity* e) override {}
        void render(Entity* e) override {}
        void handleEvent(Entity* e) override {}
    };

}