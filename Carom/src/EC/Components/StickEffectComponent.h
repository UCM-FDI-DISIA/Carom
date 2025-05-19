#pragma once

#include "Component.h"
#include "StickInputComponent.h"
#include "Entity.h"

/// @brief EL componente genérico que aplica los efectos de un palo en la bola que este golpea
class StickEffectComponent : public Component {
public:
    /// @brief La constructora de un efecto de palo
    /// @param entity La entidad a la que pertenece
    StickEffectComponent(entity_t entity) : Component(entity) {}
    virtual ~StickEffectComponent() {}

    /// @brief Método que se llama después de golpear a una bola para aplicar el efecto 
    /// @param target La bola golpeada 
    virtual void applyEffect(entity_t target) = 0;

    void update() override {}
    void handleEvent() override {}
    void render() override {}

    /// @brief Un nuevo init en el que el efecto se registra en el componente de input de un palo
    void init() override{
        if(_myEntity->tryGetComponent<StickInputComponent>()) _myEntity->getComponent<StickInputComponent>()->registerStickEffect(this);
    }
};
