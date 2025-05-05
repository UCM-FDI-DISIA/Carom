#pragma once

#include "HandleEventComponent.h"
#include <SDL.h>
#include "ecs.h"
#include "Vector2D.h"
#include "PhysicsUtils.h"

class InputHandler;

class Entity;
class RigidBodyComponent;
class RenderTextureComponent;
class TransformComponent;
class StickEffectComponent;   
class StickInputComponent : public HandleEventComponent
{
public:
    __CMPID_DECL__(cmp::STICK_INPUT);

    static constexpr float MAX_IMPULSE = 0.04f;

    StickInputComponent(Entity* e); 
    void init() override;
    void handleEvent() override;

    inline void enableBehaviour() {_behaviourEnabled = true;}
    void setEnabled(bool state) override;
    bool hasShot() { return _hasShot; }
    void transformControl(b2Vec2 _mousePos, Vector2D dirNormalized);
    void registerWhiteBall(entity_t wb);
    void registerStickEffect(StickEffectComponent* effect);
    double rad2degrees(double radians);

    inline StickEffectComponent* getStickEffect(){return _myEffect;}

private:
    InputHandler* _ih;
    entity_t _whiteBall;
    RigidBodyComponent* _whiteBallRB;
    TransformComponent* _myTransform;
    RenderTextureComponent* _myRender;
    StickEffectComponent* _myEffect;
    // --- Métodos del HandleEvents.
    bool isMouseOnCircleRadius( double r);
    float getMagFromMouseToCenter();
    // --- Area de clic de la bola.
    double _minRadiusToPull = 0.035f; // when a white ball is registred is updates to ball radius
    double _maxRadiusToPull = 0.5f;

    bool _behaviourEnabled = false;
    bool _hasShot = false;
};