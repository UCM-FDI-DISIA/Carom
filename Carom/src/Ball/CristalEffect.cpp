#include "CristalEffect.h"
#include "RigidBodyComponent.h"
#include "RenderSpritesheetComponent.h"
#include "Entity.h"
#include "CaromScene.h"
#include "ShadowComponent.h"


CristalEffect::CristalEffect(entity_t ent) 
    : BallEffect(ent)
    , _growRequest(false)
    , _myRender(ent->getComponent<RenderSpritesheetComponent>())
    , _myRB(ent->getComponent<RigidBodyComponent>())
    , _maxCollisions(4.0f)
    , _maxProportion(4.0f)
{
    _myCaromScene = dynamic_cast<CaromScene*>(&ent->getScene());


    _name = "Bola de Cristal";
    _description = "Aumenta su tamaño al chocarse con otra bola";

    _rb_initialSize = _myRB->getRadius();
    _rb_currSize = _rb_initialSize;
    _render_initialSize = _myRender->getRenderWidth(); // ! width, NO radio
    _render_currSize = _render_initialSize;

    _rb_maxSize = _rb_initialSize * _maxProportion;
    _render_maxSize = _render_initialSize * _maxProportion;

    _rb_growAmount = (_rb_maxSize - _rb_initialSize) / _maxCollisions;
    _render_growAmount = (_render_maxSize - _render_initialSize) / _maxCollisions;
}

void CristalEffect::onHit(entity_t ent)
{
    _growRequest = true;
}

void CristalEffect::grow()
{
    // auto comp = _myEntity->getComponent<ShadowComponent>();
    // _myEntity->removeComponent<ShadowComponent>();
    _rb_currSize = b2ClampFloat(_rb_currSize + _rb_growAmount, 0, _rb_maxSize);
    _render_currSize = b2ClampFloat(_render_currSize + _render_growAmount, 0, _render_maxSize);

    _myRB->setSize(_rb_currSize);
    _myRender->setNewWidth(_render_currSize);
}

bool CristalEffect::canGrow()
{
    if ((_rb_currSize < _rb_maxSize || _render_currSize < _render_maxSize)
        && _myRB->getVelocityMag() > 0.1) {

        // si necesita

        return true;

    }

    return false;
}


void CristalEffect::update()
{
    if (_growRequest && canGrow()) {
        grow();
        _growRequest = false;
    }
}

