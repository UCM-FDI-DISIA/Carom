#include "ExplosiveEffect.h"

#include "SDLUtils.h"
#include "VirtualTimer.h"
#include "CaromScene.h"
#include "RigidBodyComponent.h"
#include <cmath>
#include "Entity.h"
#include "RenderTextureComponent.h"
#include "TransformComponent.h"
#include "PhysicsUtils.h"
#include "TweenComponent.h"
#include "CameraComponent.h"
#include "AudioManager.h"

ExplosiveEffect::ExplosiveEffect(entity_t ent, float timeForExplosion, float radius, float force) 
    : BallEffect(ent), _explosionDelay(timeForExplosion), _radius(radius), _force(force), _exploded(false)
{

}

ExplosiveEffect::~ExplosiveEffect() {}

void 
ExplosiveEffect::init(){
    _explosionStart = sdlutils().currRealTime();
    _myRigidbody = _myEntity->getComponent<RigidBodyComponent>();
}

void 
ExplosiveEffect::update() {
    if(!_exploded && sdlutils().currRealTime() - _explosionStart >= _explosionDelay) {
        createExplosion();
        _exploded = true;
    }
    else if(_exploded && sdlutils().currRealTime() - _explosionStart >= _explosionDelay + 1000.0f) {
        _myEntity->removeComponent<ExplosiveEffect>();
    }
}

void 
ExplosiveEffect::createExplosion() {

    AudioManager::Instance()->playSoundEfect("explosion");
    //Agitar cámara
    _myEntity->getScene().getCamera()->shakeCamera(0.3f, 0.2f);
    //instanciar explosion

    Entity* explosionSFX = new Entity(_myEntity->getScene(), grp::FEEDBACK);

    auto texture = &sdlutils().images().at("explosion");
    float scale = _radius*2 / PhysicsConverter::pixel2meter(texture->width());


    TransformComponent* transform = new TransformComponent(explosionSFX, _myEntity->getScene().getEntitiesOfGroup(grp::WHITEBALL)[0]->getTransform()->getPosition());
    explosionSFX->addComponent<TransformComponent>(transform);
    RenderTextureComponent* renderT = new RenderTextureComponent(explosionSFX, texture, renderLayer::FEEDBACK_EFFECT, 0.0001f);

    explosionSFX->addComponent<RenderTextureComponent>(renderT);

    TweenComponent* tween = new TweenComponent(explosionSFX);
    explosionSFX->addComponent<TweenComponent>(tween);
    tween->easeScale(scale, 0.3f, tween::EASE_OUT_QUINT, false, [=](){
        explosionSFX->setAlive(false);
    });


    auto balls = _myEntity->getScene().getEntitiesOfGroup(grp::EFFECTBALLS);
    balls.push_back(_myEntity->getScene().getEntitiesOfGroup(grp::WHITEBALL)[0]);
    
    for(auto ball : balls) {
        if(ball == _myEntity) continue; //Troubleshooting para russianPyramid

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
