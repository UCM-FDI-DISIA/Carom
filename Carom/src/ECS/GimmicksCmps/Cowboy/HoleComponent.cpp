#include "HoleComponent.h"

#include "Entity.h"
#include "RenderTextureComponent.h"
#include "Vector2D.h"
#include "PhysicsUtils.h"

namespace ecs {

    HoleComponent::HoleComponent(entity_t ent, float magnitude)
        : ForceAreaComponent(ent, magnitude, true), _nearBody(nullptr), _isEmpty(true)
    {
        _myRB = _myEntity->getComponent<RigidBodyComponent>();
        defineCenter(_myRB->getPosition());
        _maxVelocityToFall = 10.0f;
        _maxDistToFall = _myRadius * 0.5f;
        _maxForce = 1.0f;
        _maxVelToTrigger = 5.0f; // above this the force doesnt work
    }

    void HoleComponent::onTriggerEnter(entity_t other)
    {
        if(other->tryGetComponent<RigidBodyComponent>()){
            // std::cout << "trigger enter" <<std::endl;
            _nearBody = other;
        }
    }

    void HoleComponent::onTriggerExit(entity_t other)
    {
    }

    // force = f(other_vel, distCenters)
    b2Vec2 HoleComponent::calculateForceToApply(entity_t e, Vector2D distanceVec, float other_vel)
    {
        float centersDistance = distanceVec.magnitude();
        // if dist = 0 forcemag = maxforce
        // if dist > radio de la bola force = 0
        float compVel = _maxForce - (b2ClampFloat(other_vel, 0, _maxVelToTrigger) * _maxForce/_maxVelToTrigger);
        float compDist = _maxForce - (b2ClampFloat(centersDistance, 0, _myRadius) * _maxForce/_myRadius);
        // std::cout << "other_vel " << b2ClampFloat(other_vel, 0, _maxVelToTrigger) << std::endl;
        // std::cout << "compVel " << compVel << std::endl;
        // std::cout << "compDist " << compDist << std::endl;
        float mag = compVel * compDist;
        distanceVec = distanceVec.normalize();
        // std::cout << "force mag: " << mag << std::endl;
        // std::cout << "calculate force x" << distanceVec.getX() * mag << std::endl;
        // std::cout << "calculate force y" << distanceVec.getY() * mag << std::endl;

        return b2Vec2(distanceVec.getX() * mag, distanceVec.getY() * mag);
    }

    
    void HoleComponent::applyForce(entity_t other)
    {
        // std::cout << "apply force x" << force.x << std::endl;
        // std::cout << "apply force y" << force.y << std::endl;
        auto other_rb = _nearBody->getComponent<RigidBodyComponent>();
        // TODO: MEJORA APPLY FORCE PERPENDICULAR TO BODY VELOCITY VECTOR
        other_rb->applyForceToCenter({_myForce.x, _myForce.y});
    }

    bool HoleComponent::tryToCapture(RigidBodyComponent* other_rb, float centersDist)
    {
        // std::cout << "try dist " << (centersDist < _maxDistToFall) << std::endl;
        // std::cout << "try vel " << (other_rb->getVelocityMag() < _maxVelocityToFall) << std::endl;
        // std::cout << "vel " << other_rb->getVelocityMag() << std::endl;
        // max velocity
        // dist center
        return centersDist < _maxDistToFall && other_rb->getVelocityMag() < _maxVelocityToFall;
    }

    void HoleComponent::update()
    {
        // std::cout << "is empty" << _isEmpty << std::endl;
        // If an object is inside sensor
        if (_nearBody) {
            // std::cout << "_nearbody" <<std::endl;
            auto other_rb = _nearBody->getComponent<RigidBodyComponent>();
            b2Vec2 other_pos = other_rb->getPosition();
            auto other_render = _nearBody->getComponent<RenderTextureComponent>();
            float other_radio = PhysicsConverter::pixel2meter(other_render->getRect().w/2);

            Vector2D distanceVec = Vector2D(_myCenter.x - other_pos.x, _myCenter.y - other_pos.y);
            float centersDistance = distanceVec.magnitude();

            // If object is in range of effect
            if (centersDistance < _myRadius){

                // std::cout << "in effect range" <<std::endl;
                // To apply a force
                float other_vel = other_rb->getVelocityMag();
                _myForce = calculateForceToApply(_nearBody, distanceVec, other_vel);
                applyForce(_nearBody);
    
                // To capture the object
                if(tryToCapture(other_rb, centersDistance))
                {
                    other_rb->setBodyEnabled(false);
                    other_rb->setPosition(_myCenter);
                    // other_rb.setVelocity(0); // TODO
                    other_render->setRenderLayer(ecs::renderLayer::POOL_HOLE);
                    other_render->changeColorTint(100, 100, 100);
                    this->setEnabled(false);
                    _isEmpty = false;
                    // ! SONIDO bola cayendo en agujero
                }
            }
        }

    }

    // Reset changes made to captured ball
    void HoleComponent::resetChanges()
    {
        // std::cout << "reset changes method hole" << std::endl;
        // std::cout << "body cap: " << _nearBody << std::endl;

        if (!_isEmpty){
            // reset physics
            auto other_rb = _nearBody->getComponent<RigidBodyComponent>();
            other_rb->setBodyEnabled(true);

            // reset render changes
            auto other_render = _nearBody->getComponent<RenderTextureComponent>();
            other_render->resetRenderLayer();
            other_render->resetColorTint();

            _nearBody = nullptr;
        }
    }


// No se usa
    // void HoleComponent::resetHole(const b2Vec2 &pos)
    // {
    //     _isEmpty = true;
    //     _myEntity->getComponent<RigidBodyComponent>()->setPosition(pos);
    //     _myRB = _myEntity->getComponent<RigidBodyComponent>();
    //     _myCenter = _myRB->getPosition();
    // }
}