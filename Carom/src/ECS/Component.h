#pragma once
#include "ecs.h"

class CameraComponent;

/// @brief La clase componente del esquema Entity-Component
class Component
{
protected:
    entity_t _myEntity;
    bool _isEnable;
public:
    /// @brief La constructora genérica de componente
    /// @param ent La entidad a la que pertenece
    Component(entity_t ent);
    virtual ~Component() = 0;

    /// @brief Mueve al componente de una entidad a otra
    /// @param other La entidad que va a recoger el componente
    inline virtual void setEntity(entity_t other) { _myEntity = other; }
    
    /// @brief Este método se llama tras ser añadido un componente a una entidad. Sirve para buscar dependencias una sola vez
    virtual void init() = 0;

    /// @brief Este método se llama cada frame, aquí se encuentra la funcionalidad de un componente físico o lógico
    virtual void update() = 0;
    /// @brief Este método se llama cada frame, aquí se encuentra la lógica de un componente de renderizado
    virtual void render() = 0;
    /// @brief Este método se llama cada vez que Game propaga un evento de sdl, se usará para recoger inputs
    virtual void handleEvent() = 0;

    /// @brief Sirve para activar y desactivar componentes
    virtual void setEnabled(bool state);

    inline entity_t getEntity() {return _myEntity;}

    bool isEnabled();
};
