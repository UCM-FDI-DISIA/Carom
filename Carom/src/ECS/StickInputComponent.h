#pragma once
#include "HandleEventComponent.h"
#include <SDL.h>
#include "ecs.h"
#include "Vector2D.h"
#include "PhysicsUtils.h"
#include "InputHandler.h"


namespace ecs{
    class Entity;
    class RigidBodyComponent;
    class StickInputComponent : public ecs::HandleEventComponent
    {
    public:
        __CMPID_DECL__(cmp::STICK_INPUT);

        /*struct Stick: public ecs::Entity {
            bool active = false;
            Vector2D pos;
            Vector2D vel;
            int width;
            int height;
            float rot;
    
            // getters stick.
            inline int stickWidth() const { return width; }
            inline int stickHeight() const { return height; }

		    // setters stick.
            inline void setStickPos(Vector2D position) { pos = position; }
            inline void setStickVel(Vector2D velocity) { vel = velocity; }
            inline void setStickRot(float rotation) { rot = rotation; }
        };*/

        StickInputComponent(Entity* e); 
        virtual ~StickInputComponent();
        void init() override;
        void handleEvent() override;

        // getters.
        inline double getRadius() { return _r; }
        inline Vector2D getCenter() { return _center; }

    private:
        // --- Métodos del HandleEvents.
        bool isOnCircleRadius(InputHandler& ih, PhysicsConverter pc, double r);
        // método para el seleccionamiento de la bola
        // método para soltar la bola.

        // --- Bola.
        Entity* _b; // entidad bola.
        RigidBodyComponent* _bRB; // transform de la bola
        bool _isBallPicked = false; // booleano de si se ha pickeado la bola.

        // --- Area de clic de la bola.
        double _r; // radio.
        Vector2D _center; // centro.
        bool _isInRadius; // para saber si está dentro del radio de la bola.
        double _maxR; // radio maximo hasta donde puede llegar la bola.

        // --- Palo.
        //Stick* s;
    };
}