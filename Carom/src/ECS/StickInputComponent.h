#pragma once

#include "HandleEventComponent.h"
#include <SDL.h>
#include "ecs.h"
#include "Vector2D.h"
#include "PhysicsUtils.h"

class InputHandler;
namespace ecs{
    class Entity;
    class RigidBodyComponent;
    class RenderTextureComponent;
    class TransformComponent;
    
    class StickInputComponent : public ecs::HandleEventComponent
    {
    public:
        __CMPID_DECL__(cmp::STICK_INPUT);

        static constexpr float MAX_IMPULSE = 0.01f;

        StickInputComponent(Entity* e, float height); 
        void init() override;
        void handleEvent() override;

        inline void enableBehaviour() {_behaviourEnabled = true;}
        void enableRender(bool active, b2Vec2 _mousePos, Vector2D dirNormalized);
        void registerWhiteBall(entity_t wb);
        double rad2degrees(double radians);

    private:
        InputHandler* _ih;
        entity_t _whiteBall;
        RigidBodyComponent* _whiteBallRB;
        TransformComponent* _myTransform;
        RenderTextureComponent* _myRender;
        // --- Métodos del HandleEvents.
        bool isMouseOnCircleRadius( double r);
        float getMagFromMouseToCenter();
        // --- Area de clic de la bola.
        double _minRadiusToPull = 0.12f;
        double _maxRadiusToPull = 0.8f;
        float _stickHeight;

        bool _behaviourEnabled = false;
    };
}