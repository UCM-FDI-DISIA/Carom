#pragma once

#include <array>
#include <vector>
#include "gameList.h"
#include "ecs.h"
#include <iostream>
#include <functional>
#include "ITransform.h"
#include "Component.h"

class CameraComponent;
namespace ecs {

    class GameScene;
    class Component;
    class CaromScene;
    class PoolScene;
    class RenderTextureComponent;
    class JsonEntityParser;
    class CowboyPoolScene;
    class EndGameScene;
    class RewardScene;
    class EndScene;

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
        bool addComponent(T* component, cmpId_t id){
            if(_components[id] != nullptr) return false;

            _components[id] = component;
            _currentComponents.push_back(component);
            
            component->init();
            
            return true;
        }

        template<typename T>
        bool addComponent(T* component){
            if(_components[cmpId<T>] != nullptr) return false;

            if(dynamic_cast<ITransform*>(component) != nullptr){
                _myTransform = dynamic_cast<ITransform*>(component);
            }

            _components[cmpId<T>] = component;
            _currentComponents.push_back(component);
            
            component->init();
            
            return true;
        }

        // Specialization for adding renderable entities to layer sort vector _entsRenderable
        template<>
        bool addComponent<RenderTextureComponent>(RenderTextureComponent* renderComp);
    
        template<typename T>
        bool removeComponent(){
            if(_components[cmpId<T>] == nullptr) return false;
    
            if(dynamic_cast<ITransform*>(_components[cmpId<T>]) != nullptr) _myTransform = nullptr;
            auto it = find(_currentComponents.begin(), _currentComponents.end(), _components[cmpId<T>]);
            _currentComponents.erase(it);
            _components[cmpId<T>] = nullptr;
    
            return true;
        }

        bool removeComponent(cmpId_t id){
            auto it = find(_currentComponents.begin(), _currentComponents.end(), _components[id]);
            _currentComponents.erase(it);
            _components[id] = nullptr;
    
            return true;
        }

        // Specialization for removing renderable entities to layer sort vector _entsRenderable
        template<>
        bool removeComponent<RenderTextureComponent>();

        template<typename T>
        bool deleteComponent(){
            if(_components[cmpId<T>] == nullptr) return false;
    
            if(dynamic_cast<ITransform*>(_components[cmpId<T>]) != nullptr) _myTransform = nullptr;
            auto it = find(_currentComponents.begin(), _currentComponents.end(), _components[cmpId<T>]);
            _currentComponents.erase(it);
            delete _components[cmpId<T>];
            _components[cmpId<T>] = nullptr;
    
            return true;
        }

        template<typename T>
        bool tryGetComponent(){
            if(_components[cmpId<T>] == nullptr) return false;
            return true;
        }

        template<typename T>
        bool tryGetComponent(T*& returnedComponent) {
            T* comp = dynamic_cast<T*>(_components[cmpId<T>]);

            if(comp == nullptr)
                return false;
            
            returnedComponent = comp;
            return true;
        }

        // template<typename T>
        // bool tryGetComponent(T* comp){
        //     if(_components[cmpId<T>] == nullptr) return false;
        //     comp = _components[cmpId<T>];
        //     return true;
        // }

        template<typename T>
        T* getComponent(){
            return static_cast<T*>(_components[cmpId<T>]);
        }

        inline ITransform* getTransform() {return _myTransform;}
        std::vector<Component*> getAllComponents(){
            return _currentComponents;
        }

        // Enables all entity's components
	    //
        void activate();

        // Disables all entity's components
        //
        void deactivate();

        void setListAnchor(GameList<Entity>::anchor&& anchor);
    
        void update();
        void render(); //En posición relativa a la cámara
        void handleEvents();

        inline GameScene& getScene() { return _myScene; }
        inline grp::grpId getID() const {return _id;};
    
    private:
        friend GameScene;
        friend CaromScene;
        friend CowboyPoolScene;
        friend PoolScene;
        friend JsonEntityParser;
        friend EndGameScene;
        friend EndScene;
        friend RewardScene;
        Entity(GameScene& scene, grpId_t gId);

        bool _alive; //El booleano alive (o active) se podría eliminar teniendo una lista separada de "entidades que no se actualizan"
        GameScene& _myScene;
        std::vector<Component*> _currentComponents;
        std::array<Component*, cmp::_LAST_CMP_ID> _components = {};
        GameList<Entity>::anchor _anchor;
        
        ITransform* _myTransform;
        grp::grpId _id;
    };
}