#pragma once

#include <array>
#include <vector>
#include <cassert>
#include "gameList.h"
#include "ecs.h"
#include <iostream>
#include <functional>
#include "ITransform.h"
#include "RenderComponent.h"
#include "Component.h"

class CameraComponent;
class GameScene;
class Component;
class CaromScene;
class PoolScene;
class JsonEntityParser;
class CowboyPoolScene;
class EndGameScene;
class RewardScene;
class UIScene;
class MainMenuScene;
class ShadowComponent;
class BallEffect;
class PauseScene;

// Magia negra para templatizar basada en clases padre
template <typename T>
concept DerivedFromRender = std::is_base_of<RenderComponent, T>::value;
template <typename T>
concept DerivedFromTransform = std::is_base_of<ITransform, T>::value;

class Entity {
    friend ShadowComponent;
public:
    virtual ~Entity();

    inline bool isAlive() {
        return _alive;
    }

    inline void setAlive(bool alive){
        _alive = alive;
    }

    template<typename T>
    bool addComponent(T* component) {
        return internalAddComponent(cmpId<T>, component);
    }

    template<>
    bool addComponent<BallEffect>(BallEffect* balleffectComp);

    template<typename T>
    bool addComponent(T* renderComp) requires DerivedFromRender<T>{

        bool r = internalAddComponent(cmpId<T>, renderComp);

        if (!r) return false;

        getSceneRenderEntities().push_back(this);

        return true;
    }

    template<typename T>
    bool addComponent(T* transformComp) requires DerivedFromTransform<T> {

        bool r = internalAddComponent(cmpId<T>, transformComp);

        if (!r) return false;

        _myTransform = transformComp;

        return true;
    }

    template<typename T>
    bool removeComponent(){
        return internalRemoveComponent(cmpId<T>);
    }

    template<typename T>
    bool removeComponent() requires DerivedFromRender<T> {

        bool r = internalRemoveComponent(cmpId<T>);

        if (!r) return false;

        std::vector<entity_t>& entsRenderable = getSceneRenderEntities();
        auto itR = find(entsRenderable.begin(), entsRenderable.end(), this);
        entsRenderable.erase(itR);

        return true;
    }

    template<typename T>
    bool removeComponent() requires DerivedFromTransform<T> {

        bool r = internalRemoveComponent(cmpId<T>);

        if (!r) return false;

        _myTransform = nullptr;

        return true;
    }

    // Sobrecarga necesitada por ballefect y derivados
    bool removeComponent(BallEffect* ballEffect);

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
    friend UIScene;
    friend RewardScene;
    friend MainMenuScene;
    friend PauseScene;
    Entity(GameScene& scene, grpId_t gId);

    bool _alive; //El booleano alive (o active) se podría eliminar teniendo una lista separada de "entidades que no se actualizan"
    GameScene& _myScene;
    std::vector<Component*> _currentComponents;
    std::array<Component*, cmp::_LAST_CMP_ID> _components = {};
    GameList<Entity>::anchor _anchor;
    
    ITransform* _myTransform;
    grp::grpId _id;


    // NO BORRAR
    // Esto está aquí para evitar dependencia circular con GameScene
    std::vector<entity_t>& getSceneRenderEntities();

    bool internalAddComponent(cmpId_t id, Component* component);
    bool internalRemoveComponent(cmpId_t id);
};