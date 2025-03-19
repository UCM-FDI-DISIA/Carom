#include "ExplosiveEffect.h"

#include "SDLUtils.h"
#include "VirtualTimer.h"
#include "CaromScene.h"
#include "RigidBodyComponent.h"
#include "PushOutsideTriggerComponent.h"

namespace ecs {
    ExplosiveEffect::ExplosiveEffect(entity_t ent, float timeForExplosion, float radius, float force) 
        : BallEffect(ent), _explosionDelay(timeForExplosion), _radius(radius), _force(force)
    {

    }

    ExplosiveEffect::~ExplosiveEffect() {}

    void 
    ExplosiveEffect::init(){
        _explosionStart = sdlutils().virtualTimer().currTime();
    }

    void 
    ExplosiveEffect::update() {
        if(!_exploded && sdlutils().virtualTimer().currTime() - _explosionStart >= _explosionDelay) {
            //Agitar cámara

            b2BodyId ID = _myEntity->getComponent<RigidBodyComponent>()->getB2Body();

            b2ShapeDef* shape = new b2ShapeDef(b2DefaultShapeDef());
            shape->userData = _myEntity;
            shape->isSensor = true;

            b2Circle circle;
            circle.radius = _radius;
            circle.center = {0, 0};
            _id = b2CreateCircleShape(ID, shape, &circle);
        }
        else if(_exploded && sdlutils().virtualTimer().currTime() - _explosionStart >= _explosionDelay + 1.0f) {
            b2DestroyShape(_id, false);
            _myEntity->removeComponent<ExplosiveEffect>();
        }
    }
}