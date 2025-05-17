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
    , _maxProportion(2.5f)
    , _isBig(false)
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
    _rb_currSize = b2ClampFloat(_rb_currSize + _rb_growAmount, 0, _rb_maxSize);
    _render_currSize = b2ClampFloat(_render_currSize + _render_growAmount, 0, _render_maxSize);
    
    _myRB->setSize(_rb_currSize);
    _myRender->setNewWidth(_render_currSize);
    
    auto shadows = _myEntity->getComponent<ShadowComponent>()->getShadows();

    for (auto& s : shadows) {
        s->getComponent<RenderTextureComponent>()->setNewWidth(_render_currSize);
    }

    _isBig = true;
}

bool CristalEffect::canGrow()
{
    if ((_rb_currSize < _rb_maxSize || _render_currSize < _render_maxSize)
        && _myRB->getVelocityMag() > 0.1
        && noNearbyBodies()) {

        
        
        return true;

    }

    return false;
}


void CristalEffect::update()
{
    if (_growRequest && canGrow()) {
        grow();
        _growRequest = false;
        // noNearbyBodies();
    }

    // noNearbyBodies();
}

bool CristalEffect::noNearbyBodies()
{
    Vector2D dir =  Vector2D(1, 0);

    constexpr float lines = 10;
    constexpr float delta = 2.0f * B2_PI / lines;

    bool isFar = true;

    for (float i = 0; i <= 2.0f * B2_PI && isFar; i += delta)
    {
        dir.setX(dir.getX() * cos(i) - dir.getY() * sin(i));
        dir.setY(dir.getX() * cos(i) + dir.getY() * sin(i));
        dir.normalize();

        float a_cosalpha = dir.normalize() * Vector2D(1, 0);
        float a_sinalpha = dir.normalize() * Vector2D(0, 1);

        float a_ballRadius = _rb_currSize;

        b2Vec2 a_ballCenter = { _myRB->getPosition().x, _myRB->getPosition().y};

        b2Vec2 a_ballBorder = b2Vec2(
            a_ballCenter.x + dir.getX() * a_ballRadius, 
            a_ballCenter.y + dir.getY() * a_ballRadius
        );

        b2RayResult rayResult = _myCaromScene->castRayToWorld(a_ballCenter, 
            b2Vec2((a_ballCenter.x + dir.getX() * 100.f), (a_ballCenter.y + dir.getY() * 100.f)));

        // Si alguien pregunta por como va esta mierda, ya ni se como va, maldigo a la geometría

        float dist = b2Length(rayResult.point - a_ballCenter);

        isFar = dist > (a_ballRadius + _rb_growAmount) * 2.0f;

    }

    return isFar;
}

