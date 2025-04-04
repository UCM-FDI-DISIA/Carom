#pragma once

#include <array>
#include <vector>
#include "gameList.h"
#include "ecs.h"
#include <iostream>
#include "ITransform.h"
#include "RenderComponent.h"

class Camera;

class GameScene;
class Component;
class CaromScene;
class PoolScene;

// Magia negra para templatizar basada en clases padre
template <typename T>
concept DerivedFromRender = std::is_base_of<RenderComponent, T>::value;
template <typename T>
concept DerivedFromTransform = std::is_base_of<ITransform, T>::value;

class Entity {
public:
    virtual ~Entity();

    inline bool isAlive() {
        return _alive;
    }

    inline void setAlive(bool alive){
        _alive = alive;
    }

    template<typename T>
    bool addComponent(T* component) requires (!DerivedFromRender<T> && !DerivedFromTransform<T>){
        return internalAddComponent(component);
    }

    template<typename T>
    bool addComponent(T* renderComp) requires DerivedFromRender<T>{

        bool r = internalAddComponent(renderComp);

        if (!r) return false;

        getSceneRenderEntities().push_back(this);

        return true;
    }

    template<typename T>
    bool addComponent(T* transformComp) requires DerivedFromTransform<T> {

        bool r = internalAddComponent(transformComp);

        if (!r) return false;

        _myTransform = transformComp;

        return true;
    }

    template<typename T>
    bool removeComponent(){
        internalRemoveComponent<T>();
    }


    template<typename T>
    bool removeComponent() requires DerivedFromRender<T> {

        bool r = internalRemoveComponent<T>();

        if (!r) return false;

        std::vector<entity_t>& entsRenderable = getSceneRenderEntities();
        auto itR = find(entsRenderable.begin(), entsRenderable.end(), this);
        entsRenderable.erase(itR);

        return true;
    }

    template<typename T>
    bool removeComponent() requires DerivedFromTransform<T> {

        bool r = internalRemoveComponent<T>();

        if (!r) return false;

        _myTransform = nullptr;

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
    void render(Camera* camera); //En posición relativa a la cámara
    void handleEvents();

    GameScene& getScene();

private:
    friend GameScene;
    friend CaromScene;
    friend PoolScene;
    Entity(GameScene& scene, grpId_t gId);

    bool _alive; //El booleano alive (o active) se podría eliminar teniendo una lista separada de "entidades que no se actualizan"
    GameScene& _myScene;
    std::vector<Component*> _currentComponents;
    std::array<Component*, cmp::_LAST_CMP_ID> _components = {};
    GameList<Entity>::anchor _anchor;
    
    ITransform* _myTransform;

    std::vector<entity_t>& getSceneRenderEntities();

    template<typename T>
    bool internalAddComponent(T* component) {
        if(_components[cmpId<T>] != nullptr) return false;

        _components[cmpId<T>] = component;
        _currentComponents.push_back(component);
        _components[cmpId<T>]->init();

        return true;
    }

    template<typename T>
    bool internalRemoveComponent(T* component) {
        if(_components[cmpId<T>] == nullptr) return false;

        auto it = find(_currentComponents.begin(), _currentComponents.end(), _components[cmpId<T>]);
        _currentComponents.erase(it);

        delete _components[cmpId<T>];

        _components[cmpId<T>] = nullptr;

        return true;
    }
};