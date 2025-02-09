#pragma once

#include<array>
#include<vector>

class Component;

namespace ecs {

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

        /// @brief GetComponent de Unity
        /// @param  ComponentID Id del componente solicitado
        /// @param  Component Referencia donde se devuelve el componente solicitado o el puntero a nulo si no existe
        /// @return true si la entidad tiene el componente, false si no
        bool tryGetComponent(ComponentID, Component*&);
    
        void update();
        void render();
        void handleEvents();
    
    private:
        bool _alive; //El booleano alive (o active) se podría eliminar teniendo una lista separada de "entidades que no se actualizan"
    
        std::vector<Component*> _currentComponents;
        std::array<Component*, NUM_COMPONENTS> _components;
    };
}