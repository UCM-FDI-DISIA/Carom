#pragma once

#include<array>
#include<vector>
#include "gameList.h"

class Component;

namespace ecs {

    enum ComponentID {
        TRANSFORM,
        RENDER_TEXTURE,
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
        template<typename T>
        bool tryGetComponent(ComponentID ID, T*& component){
            if(_components[ID] == nullptr) return false;

            component = _components[ID];
            return true;
        }

        template<typename T>
        T* getComponent(ComponentID ID){
            return _components[ID];
        }

        void update();
        void render();
        void handleEvents();
    
    private:
        bool _alive; //El booleano alive (o active) se podría eliminar teniendo una lista separada de "entidades que no se actualizan"
    
        std::vector<Component*> _currentComponents;
        std::array<Component*, NUM_COMPONENTS> _components;
        GameList<Entity>::anchor _anchor;
    };
}