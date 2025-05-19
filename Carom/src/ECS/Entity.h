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
class ControlsScene;
class ShadowComponent;
class PauseScene;
class TutorialScene;
class TextHelperScene;
class QuitScene;
class StickRewardScene;
class BossRewardScene;
class CauldronRewardScene;
class ExplosiveEffect;

// Magia negra para templatizar basada en clases padre
template <typename T>
concept DerivedFromRender = std::is_base_of<RenderComponent, T>::value;
template <typename T>
concept DerivedFromTransform = std::is_base_of<ITransform, T>::value;
template <typename T> 
concept DerivedFromBallEffect = std::is_base_of<BallEffect, T>::value;

/// @brief La clase entidad del esquema entity-component
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

    /// @brief Método genérico para añadir componentes
    /// @tparam T Clase del componente 
    /// @param component componente a añadir 
    /// @return true si se añade el componente, false si no 
    template<typename T>
    bool addComponent(T* component) {
        return internalAddComponent(cmpId<T>, component);
    }

    /// @brief Addcomponent sobrecargado para efectos de bola, existe porque todos los efectos deben ir a la lista de BallHandler
    template<typename T>
    bool addComponent(T* ballEffectComp) requires DerivedFromBallEffect<T> {
        auto ballHandler = getComponent<BallHandler>();
        ballHandler->addEffect(ballEffectComp);
        return internalAddComponent(ballEffectComp->getEffectId(), ballEffectComp);
    }

    /// @brief Addcomponent sobrecargado para componentes de render, así se asegura el orden de las capas al renderizar
    /// @tparam T 
    /// @param renderComp 
    /// @return 
    template<typename T>
    bool addComponent(T* renderComp) requires DerivedFromRender<T>{

        bool r = internalAddComponent(cmpId<T>, renderComp);

        if (!r) return false;

        _myRenderer = renderComp;
        addToSceneRenderEntities(this);

        return true;
    }

    /// @brief Addcomponent sobrecargado para transforms, puesto que hay transform físico y lógico
    template<typename T>
    bool addComponent(T* transformComp) requires DerivedFromTransform<T> {

        bool r = internalAddComponent(cmpId<T>, transformComp);

        if (!r) return false;

        _myTransform = transformComp;

        return true;
    }

    /// @brief Método genérico para eliminar un componente de tipo T
    /// @return true si se ha eliminado, false si no
    template<typename T>
    bool removeComponent(){
        return internalRemoveComponent(cmpId<T>);
    }

    //----------------------------------------------------------
    //Los siguientes métodos son sobrecargas iguales que las anteriores

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

    //----------------------------------------------------------------

    /// @brief Úsalo como un hasComponent()
    /// @return true si tiene el componente, false si no 
    template<typename T>
    bool tryGetComponent(){
        if(_components[cmpId<T>] == nullptr) return false;
        return true;
    }

    /// @brief Un getComponent que además devuelve booleano para asegurar que el componente devuelto es válido 
    /// @param returnedComponent La referencia al componente donde va a parar el componente devuelto
    /// @return true si tiene el componente, false si no 
    template<typename T>
    bool tryGetComponent(T*& returnedComponent) {
        T* comp = dynamic_cast<T*>(_components[cmpId<T>]);

        if(comp == nullptr)
            return false;
        
        returnedComponent = comp;
        return true;
    }

    /// @brief Getter genérico de componentes
    /// @return El componente si lo tiene, nullptr si no
    template<typename T>
    T* getComponent(){
        return static_cast<T*>(_components[cmpId<T>]);
    }

    /// @brief Roba un componente de otra entidad, no funciona en efectos, render o transform
    /// @param from entidad a la que le robas el componente
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

    /// @brief Sobrecarga de stealComponent para efectos de bola
    /// @param from Entidad a la que le robas el componente
    /// @param effect el efecto a robar
    void stealComponent(entity_t from, BallEffect* effect){
        bool s = from->internalRemoveComponent(effect->getEffectId(), false);
        assert(s);

        effect->setEntity(this);
        getComponent<BallHandler>()->addEffect(effect);
        s = this->internalAddComponent(effect->getEffectId(), effect, true);
        assert(s);
    }

    inline ITransform* getTransform() {return _myTransform;}
    std::vector<Component*> getAllComponents(){
        return _currentComponents;
    }

    inline RenderComponent* getRenderer() {return _myRenderer;}

    /// @brief Enables all entity's components
    void activate();

    /// @brief Disables all entity's components
    void deactivate();

    /// @brief Activa todos los componentes de un tipo T
    template<typename T>
    void activateComponentsOfType() {
        for(Component* component : _currentComponents)
            if(dynamic_cast<T*>(component) != nullptr) component->setEnabled(true);
    }

    /// @brief desactiva todos los componentes de un tipo T
    template<typename T>
    void deactivateComponentsOfType() {
        for(Component* component : _currentComponents)
            if(dynamic_cast<T*>(component) != nullptr) component->setEnabled(false);
    }

    void setGameScene(GameScene* scene);

    /// @brief Una cosa necesaria para usar la lista de Mr. Rubén C++ 
    void setListAnchor(GameList<Entity>::anchor&& anchor);

    /// @brief Llama al update de todos sus componentes
    void update();
    /// @brief Llama al render de todos sus componentes
    void render(); //En posición relativa a la cámara
    /// @brief Llama al handleEvent de todos sus componentes
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
    friend ControlsScene;
    friend PauseScene;
    friend RussianPyramidScene;
    friend TutorialScene;
    friend TextHelperScene;
    friend CauldronRewardScene;
    friend QuitScene;
    friend StickRewardScene;
    friend BossRewardScene;
    friend ExplosiveEffect;

    /// @brief La constructora es privada por temas que no recuerdo, ahora es bastante pointless, pero tiene muchos amigos
    /// @param scene La escena en la que se crea la entidad 
    /// @param gId El grupo al que pertenece la entidad 
    Entity(GameScene& scene, grpId_t gId);

    bool _alive; //El booleano alive (o active) se podría eliminar teniendo una lista separada de "entidades que no se actualizan"
    GameScene& _myScene;
    std::vector<Component*> _currentComponents;
    std::array<Component*, cmp::_LAST_CMP_ID> _components = {};
    GameList<Entity>::anchor _anchor;
    
    ITransform* _myTransform;
    grp::grpId _id;

    RenderComponent* _myRenderer;

    //Métodos para manejar el render de entidades por capas
    const std::vector<entity_t>& getSceneRenderEntities();
    void eraseFromRenderEntities(entity_t e);
    void addToSceneRenderEntities(entity_t e);

    // Métodos auxiliares para evitar duplicidad de código en sobrecargas
    bool internalAddComponent(cmpId_t id, Component* component, bool initCmp = true);
    bool internalRemoveComponent(cmpId_t id, bool deleteCmp = true);
};