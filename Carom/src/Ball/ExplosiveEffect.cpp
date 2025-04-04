#include "ExplosiveEffect.h"

#include "SDLUtils.h"
#include "VirtualTimer.h"
#include "CaromScene.h"
#include "RigidBodyComponent.h"
#include <cmath>


ExplosiveEffect::ExplosiveEffect(entity_t ent, float timeForExplosion, float radius, float force) 
    : BallEffect(ent), _explosionDelay(timeForExplosion), _radius(radius), _force(force), _exploded(false)
{

}

ExplosiveEffect::~ExplosiveEffect() {}

void 
ExplosiveEffect::init(){
    _explosionStart = sdlutils().virtualTimer().currTime();
    _myRigidbody = _myEntity->getComponent<RigidBodyComponent>();
}

void 
ExplosiveEffect::update() {
    if(!_exploded && sdlutils().virtualTimer().currTime() - _explosionStart >= _explosionDelay) {
        createExplosion();
        _exploded = true;
    }
    else if(_exploded && sdlutils().virtualTimer().currTime() - _explosionStart >= _explosionDelay + 1000.0f) {
        _myEntity->removeComponent<ExplosiveEffect>();
    }
}

void 
ExplosiveEffect::createExplosion() {
    //Agitar cámara
    //TODO transformar esto en una entidad con el componente de empuje
    auto balls = _myEntity->getScene().getEntitiesOfGroup(grp::EFFECTBALLS);
    
    for(auto ball : balls) {
        auto targetRB = ball->getComponent<RigidBodyComponent>();
        b2Vec2 distance = targetRB->getPosition() - _myRigidbody->getPosition();

        float distanceMagnitude = Vector2D(distance.x, distance.y).magnitude();

        if(distanceMagnitude < _radius) {
            b2Vec2 direction = b2Normalize(distance);
            float quadraticInverseDistance = 1 / std::pow(distanceMagnitude, 2);
            targetRB->applyForceToCenter((direction * _force) * quadraticInverseDistance);
        }
    }
}
