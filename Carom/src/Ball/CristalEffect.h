#pragma once
#include "BallEffect.h"

class CaromScene;
class RigidBodyComponent;
class RenderSpritesheetComponent;

class CristalEffect : public BallEffect
{
public:
    CristalEffect(entity_t ent);
    ~CristalEffect() {}
    
    void onHit(entity_t ent) override;
    void update() override;

    // si no hay bodies cerca puede aumentar
    bool canGrow();
    // cambia tamano render y physical body
    void grow();


    __CMPID_DECL__(cmp::CRISTAL_EFFECT);
    cmpId_t getEffectId() override {return cmp::CRISTAL_EFFECT;};

private:
    RigidBodyComponent* _myRB;
    RenderSpritesheetComponent* _myRender;
    CaromScene* _myCaromScene;

    bool _growRequest; // true when hit
    
    // separados por errores de precision al escalar
    float _rb_initialSize; // rigidbody size
    float _render_initialSize;
    
    float _rb_currSize;
    float _render_currSize;

    
    
    float _rb_growAmount;
    float _render_growAmount;

    float _maxProportion; // max grow size / initial size = doble
    float _rb_maxSize;
    float _render_maxSize;

    float _maxCollisions; // numero de colisiones hasta tamano final
};