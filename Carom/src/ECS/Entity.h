#pragma once

#include <array>
#include <vector>
#include "gameList.h"
#include "ecs.h"
#include <iostream>


class Camera;
namespace ecs {

    class GameScene;
    class Component;
    class ITransform;
    class CaromScene;

    class Entity{
    public:
        virtual ~Entity();
    
        inline bool isAlive() {
            return _alive;
        }
    
        inline void setAlive(bool alive){
            _alive = alive;
        }
    
        template<typename T>
        bool addComponent(T* component){
            if(_components[cmpId<T>] != nullptr) return false;

            // Asigna el transform de la entidad en caso de que no exista ninguno
            if (dynamic_cast<ITransform*>(component) != nullptr) {
                    _myTransform = dynamic_cast<ITransform*>(component);
            }

            _components[cmpId<T>] = component;
            _currentComponents.push_back(component);
    
            _components[cmpId<T>]->init();
    
            return true;
        }
    
        template<typename T>
        bool removeComponent(){
            if(_components[cmpId<T>] == nullptr) return false;
    
            if(dynamic_cast<ITransform>(_components[cmpId<T>] != nullptr)) _myTransform = nullptr;
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

        inline ITransform* getTransform() {return _myTransform;}

        void setListAnchor(GameList<Entity>::anchor&& anchor);
    
        void update();
        void render(Camera* camera); //En posición relativa a la cámara
        void handleEvents();

        GameScene& getScene();
    
    private:
        friend GameScene;
        friend CaromScene;
        Entity(GameScene& scene);

        bool _alive; //El booleano alive (o active) se podría eliminar teniendo una lista separada de "entidades que no se actualizan"
        GameScene& _myScene;
        std::vector<Component*> _currentComponents;
        std::array<Component*, cmp::_LAST_CMP_ID> _components = {};
        GameList<Entity>::anchor _anchor;

        ITransform* _myTransform;
    };
}