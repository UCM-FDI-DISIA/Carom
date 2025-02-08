#pragma once

#include<array>
#include<vector>

class Component;

namespace ecs{

    enum ComponentID {
        NUM_COMPONENTS
    };

    class Entity{
    public:
        Entity();
        ~Entity();
    
        inline bool isAlive() {
            return _alive;
        }
    
        inline void setAlive(bool alive){
            _alive = alive;
        }
    
        bool addComponent(Component*, ComponentID);
    
        bool removeComponent(ComponentID);

        Component* getComponent(ComponentID);
    
        void update();
        void render();
        void handleEvents();
    
    private:
        bool _alive;
    
        std::vector<Component*> _currentComponents;
        std::array<Component*, NUM_COMPONENTS> _components;
    };
}