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
#include "BallEffect.h"
#include "BallHandler.h"

class CameraComponent;
class GameScene;
class Component;
class CaromScene;
class PoolScene;
class JsonEntityParser;
class CowboyPoolScene;
class RussianPyramidScene;
class EndGameScene;
class RewardScene;
class UIScene;
class MainMenuScene;
class ShadowComponent;
class PauseScene;
class TutorialScene;
class TextHelperScene;
class QuitScene;
class StickRewardScene;
class BossRewardScene;

// Magia negra para templatizar basada en clases padre
template <typename T>
concept DerivedFromRender = std::is_base_of<RenderComponent, T>::value;
template <typename T>
concept DerivedFromTransform = std::is_base_of<ITransform, T>::value;
template <typename T> 
concept DerivedFromBallEffect = std::is_base_of<BallEffect, T>::value;

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

    template<typename T>
    bool addComponent(T* ballEffectComp) requires DerivedFromBallEffect<T> {
        auto ballHandler = getComponent<BallHandler>();
        ballHandler->addEffect(ballEffectComp);
        return internalAddComponent(ballEffectComp->getEffectId(), ballEffectComp);
    }

    template<typename T>
    bool addComponent(T* renderComp) requires DerivedFromRender<T>{

        bool r = internalAddComponent(cmpId<T>, renderComp);

        if (!r) return false;

        _myRenderer = renderComp;
        addToSceneRenderEntities(this);

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

        _myRenderer = nullptr;
        eraseFromRenderEntities(this);

        return true;
    }

    template<typename T>
    bool removeComponent() requires DerivedFromTransform<T> {

        bool r = internalRemoveComponent(cmpId<T>);

        if (!r) return false;

        _myTransform = nullptr;

        return true;
    }

    template<typename T>
    bool removeComponent() requires DerivedFromBallEffect<T> {
        auto ballHandler = getComponent<BallHandler>();
        auto effect = getComponent<T>();
        ballHandler->removeEffect(effect);
        return internalRemoveComponent(effect->getEffectId());
    }

    bool removeComponent(BallEffect* ballEffect) {
        auto ballHandler = getComponent<BallHandler>();
        ballHandler->removeEffect(ballEffect);
        return internalRemoveComponent(ballEffect->getEffectId());
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

    template<typename T>
    T* getComponent(){
        return static_cast<T*>(_components[cmpId<T>]);
    }

    // ! IMPORTANTE : NO ESTA PENSADO PARA USAR EN TRANSFORM O RENDER
    // hay que mirar a ver si funcionaria
    template<typename T>
    void stealComponent(entity_t from){
        assert(from->tryGetComponent<T>() && !this->tryGetComponent<T>());

        T* cmp = from->getComponent<T>();
        cmp->setEntity(this);
        bool s = this->internalAddComponent(cmpId<T>, cmp, false);
        assert(s);

        s = from->internalRemoveComponent(cmpId<T>, false);
        assert(s);
    }

    inline ITransform* getTransform() {return _myTransform;}
    std::vector<Component*> getAllComponents(){
        return _currentComponents;
    }

    inline RenderComponent* getRenderer() {return _myRenderer;}

    // Enables all entity's components
    //
    void activate();

    // Disables all entity's components
    //
    void deactivate();

    template<typename T>
    void activateComponentsOfType() {
        for(Component* component : _currentComponents)
            if(dynamic_cast<T*>(component) != nullptr) component->setEnabled(true);
    }

    template<typename T>
    void deactivateComponentsOfType() {
        for(Component* component : _currentComponents)
            if(dynamic_cast<T*>(component) != nullptr) component->setEnabled(false);
    }

    void setGameScene(GameScene* scene);

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
    friend RussianPyramidScene;
    friend TutorialScene;
    friend TextHelperScene;
    friend QuitScene;
    friend StickRewardScene;
    friend BossRewardScene;

    Entity(GameScene& scene, grpId_t gId);

    bool _alive; //El booleano alive (o active) se podría eliminar teniendo una lista separada de "entidades que no se actualizan"
    GameScene& _myScene;
    std::vector<Component*> _currentComponents;
    std::array<Component*, cmp::_LAST_CMP_ID> _components = {};
    GameList<Entity>::anchor _anchor;
    
    ITransform* _myTransform;
    grp::grpId _id;

    RenderComponent* _myRenderer;

    // NO BORRAR
    // Esto está aquí para evitar dependencia circular con GameScene
    const std::vector<entity_t>& getSceneRenderEntities();
    void eraseFromRenderEntities(entity_t e);
    void addToSceneRenderEntities(entity_t e);

    bool internalAddComponent(cmpId_t id, Component* component, bool initCmp = true);
    bool internalRemoveComponent(cmpId_t id, bool deleteCmp = true);
};