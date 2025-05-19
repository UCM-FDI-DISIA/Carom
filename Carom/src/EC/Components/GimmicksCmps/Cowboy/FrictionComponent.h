#pragma once

#include "ForceFieldComponent.h"


// Componente que se añade a una entidad con cuerpo rígido configurado como sensor
// Los objetos dentro reciben una fuerza contraria durante el movimiento
// No se usa el parámetro linearDamping por dos razones:
// - Evitar conflictos con la habilidad de stick
// - Reutilizar la lógica para componentes tipo campo de fuerza
class FrictionComponent : public ForceFieldComponent
{ 
    float _mu; // friction coeficient (no distinction dynamic/static)
    
public:
    __CMPID_DECL__(cmp::FRICTION);
    
    FrictionComponent(entity_t ent, float frictionCoef = 2);
    virtual ~FrictionComponent() {}
    
protected:
    virtual void applyForce(RigidBodyComponent* rb) override;
    virtual void calculateMyForceVector(RigidBodyComponent* rb, const Vector2D& direction);
};