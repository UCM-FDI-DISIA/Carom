#pragma once

#include <array>
#include <vector>
#include "gameList.h"
#include "ecs.h"

class CaromScene;

namespace ecs {

    class GameScene;

    class Entity{
    public:
        virtual ~Entity();
    
        inline bool isAlive() {
            return _alive;
        }
    
        inline void setAlive(bool alive){
            _alive = alive;
        }
    
        template<typename T, typename ...Ts>
        bool addComponent(T* component, Ts &&... args){
            if(_components[cmpId<T>] != nullptr) return false;
    
            _components[cmpId<T>] = component;
            _currentComponents.push_back(component);
    
            _components[cmpId<T>]->init();
    
            return true;
        }
    
        template<typename T>
        bool removeComponent(){
            if(_components[cmpId<T>] == nullptr) return false;
    
            auto it = find(_currentComponents.begin(), _currentComponents.end(), _components[cmpId<T>]);
            _currentComponents.erase(it);
            _components[cmpId<T>] = nullptr;
    
            return true;
        }

        template<typename T>
        bool tryGetComponent(){
            if(_components[cmpId<T>] == nullptr) return false;

            return true;
        }

        template<typename T>
        T* getComponent(){
            return static_cast<T*>(_components[cmpId<T>]);
        }

        std::vector<Component*> getAllComponents(){
            return _currentComponents;
        }

        // Enables all entity's components
	    //
        void enable();

        // Disables all entity's components
        //
        inline void disable();

        void setListAnchor(GameList<Entity>::anchor&& anchor);
    
        void update();
        void render();
        void handleEvents();
    
    private:
        friend GameScene;
        friend CaromScene;
        Entity(GameScene& scene);

        bool _alive; //El booleano alive (o active) se podría eliminar teniendo una lista separada de "entidades que no se actualizan"
        GameScene& _myScene;
        std::vector<Component*> _currentComponents;
        std::array<Component*, cmp::_LAST_CMP_ID> _components = {};
        GameList<Entity>::anchor _anchor;
    };
}