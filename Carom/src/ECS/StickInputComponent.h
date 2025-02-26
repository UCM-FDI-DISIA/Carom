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
    
    class StickInputComponent : public ecs::HandleEventComponent
    {
    public:
        __CMPID_DECL__(cmp::STICK_INPUT);

        StickInputComponent(Entity* e); 
        void init() override;
        void handleEvent() override;

        inline void enableBehaviour() {_behaviourEnabled = true;}

    private:
    InputHandler* _ih;
        // --- Métodos del HandleEvents.
        bool isMouseOnCircleRadius( double r);
        // --- Area de clic de la bola.
        double _minRadiusToPull = 0.5f;
        double _maxRadiusToPull = 4;

        bool _behaviourEnabled = false;
    };
}