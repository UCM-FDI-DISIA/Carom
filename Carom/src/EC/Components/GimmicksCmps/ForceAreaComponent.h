#pragma once

#include <box2d/box2d.h>
#include "Vector2D.h"

#include "PhysicsComponent.h"
#include "ForceFieldComponent.h"


// Componente que define la fuerza del campo: magnitud y si es atractiva o repulsiva.
// Por defecto, la fuerza tiene la dirección desde el centro del otro cuerpo hacia el centro de este cuerpo.
// Esta clase puede ser heredada para sobreescribir y personalizar la definición de la fuerza 
// y las condiciones en las que se aplica la fuerza.
class ForceAreaComponent : public ForceFieldComponent
{
protected:
    b2Vec2 _myCenter;
    float _minMagnitude;
    bool _attraction;
    float _maxVelToTrigger; // above this the body ignores the force

public:
    __CMPID_DECL__(cmp::FORCE_AREA);
    
    // If attraction is false the force is repulsion
    ForceAreaComponent(entity_t ent, float magnitude, bool attraction = true);
    virtual ~ForceAreaComponent() {}

protected:
    virtual void defineForce(entity_t e);
    virtual void applyForce(entity_t e) = 0;

    virtual void defineCenter(b2Vec2 c);
};