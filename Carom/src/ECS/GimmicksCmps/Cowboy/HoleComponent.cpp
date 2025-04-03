#include "HoleComponent.h"

#include "Entity.h"
#include "Vector2D.h"
#include "PhysicsUtils.h"



HoleComponent::HoleComponent(entity_t ent, float magnitude)
    : ForceAreaComponent(ent, magnitude, true)
    , _contextEntt(nullptr)
    , _isEmpty(true)
{
    _myRB = _myEntity->getComponent<RigidBodyComponent>();
    defineCenter(_myRB->getPosition());
    _maxVelocityToFall = 10.0f;
    _maxDistToFall = _myRadius * 0.5f;
    _maxForce = 1.0f;
    _maxVelToTrigger = 9.0f; // above this the force doesnt work
}

void HoleComponent::onTriggerEnter(entity_t other)
{
    if(_isEmpty && other->tryGetComponent<RigidBodyComponent>()) { 
        _contextEntt = other;
        _contextRB = _contextEntt->getComponent<RigidBodyComponent>();
        _contextRender = _contextEntt->getComponent<RenderTextureComponent>();
    }
}

void HoleComponent::onTriggerExit(entity_t other)
{
    if(_isEmpty && _contextEntt == other) {
        _contextEntt = nullptr;
    }
}

// force = f(other_vel, distCenters)
b2Vec2 HoleComponent::calculateForceToApply(Vector2D distanceVec)
{
    float centersDistance = distanceVec.magnitude();

    float compVel = _maxForce - (b2ClampFloat(_contextRB->getVelocityMag(), 0, _maxVelToTrigger) * _maxForce/_maxVelToTrigger);
    float compDist = _maxForce - (b2ClampFloat(centersDistance, 0, _myRadius) * _maxForce/_myRadius);

    float mag = compVel * compDist;
    distanceVec = distanceVec.normalize();

    return b2Vec2(distanceVec.getX() * mag, distanceVec.getY() * mag);
}


void HoleComponent::applyForce(entity_t other)
{
    _contextRB->applyForceToCenter({_myForce.x, _myForce.y});
}

bool HoleComponent::tryToCapture(float centersDist)
{
    return centersDist < _maxDistToFall 
        && _contextRB->getVelocityMag() < _maxVelocityToFall;
}

void HoleComponent::update()
{
    // If an object is inside sensor
    if (_isEmpty && _contextEntt) 
    {
        b2Vec2 contextPos = _contextRB->getPosition();
        float contextRadius = PhysicsConverter::pixel2meter(_contextRender->getRenderRect().w/2);

        Vector2D distanceVec = Vector2D(_myCenter.x - contextPos.x, _myCenter.y - contextPos.y);
        float centersDistance = distanceVec.magnitude();

        // If object is in range of effect
        if (centersDistance < _myRadius)
        {
            // To apply a force
            _myForce = calculateForceToApply(distanceVec);
            applyForce(_contextEntt);

            // To capture the object
            if(tryToCapture(centersDistance))
            {
                b2Body_SetLinearVelocity(_contextRB->getB2Body(), b2Vec2_zero);
                b2Body_SetAngularVelocity(_contextRB->getB2Body(), 0.0f);
                _myForce = -_myForce;
                applyForce(_contextEntt);
                
                _contextRB->setBodyEnabled(false);
                _contextRB->setPosition(_myCenter);

                _contextRender->setRenderLayer(renderLayer::POOL_HOLE);
                _contextRender->changeColorTint(100, 100, 100);
                _isEmpty = false;
                // ! SONIDO bola cayendo en agujero
            }
        }
    }

}

// Reset changes made to captured ball
void HoleComponent::resetChanges()
{
    if (!_isEmpty)
    {
        // reset physics
        _contextRB->setBodyEnabled(true);

        // reset render changes
        _contextRender->resetRenderLayer();
        _contextRender->resetColorTint();
    }
}