#include "ExplosiveEffect.h"

#include "SDLUtils.h"
#include "VirtualTimer.h"
#include "CaromScene.h"
#include "RigidBodyComponent.h"
#include "PushOutsideTriggerComponent.h"

namespace ecs {
    ExplosiveEffect::ExplosiveEffect(entity_t ent, float timeForExplosion, float radius, float force) 
        : BallEffect(ent), _explosionDelay(timeForExplosion), _radius(radius), _force(force), _exploded(false)
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
            createExplosion();
            _exploded;
        }
        else if(_exploded && sdlutils().virtualTimer().currTime() - _explosionStart >= _explosionDelay + 1000.0f) {
            b2DestroyShape(_id, false);
            _myEntity->removeComponent<ExplosiveEffect>();
            _myEntity->removeComponent<PushOutsideTriggerComponent>();
        }
    }

    void 
    ExplosiveEffect::createExplosion() {
        //Agitar cámara
        //TODO transformar esto en una entidad con el componente de empuje
        b2BodyId body = _myEntity->getComponent<RigidBodyComponent>()->getB2Body();

        b2ShapeDef* shape = new b2ShapeDef(b2DefaultShapeDef());
        shape->userData = _myEntity;
        shape->isSensor = true;

        b2Circle circle;
        circle.radius = _radius;
        circle.center = {0, 0};

        _id = b2CreateCircleShape(body, shape, &circle);

        _myEntity->addComponent<PushOutsideTriggerComponent>(new PushOutsideTriggerComponent(_myEntity, _force));
    }

}