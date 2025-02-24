#pragma once
#include "Component.h"
#include <SDL.h>
#include "ecs.h"
#include "Vector2D.h"
#include "ITransform.h"

class Entity;

namespace ecs{
    class StickInputComponent : public ecs::Component
    {
    public:
        __CMPID_DECL__(cmp::STICK_INPUT);

        StickInputComponent(Entity* e, ITransform* t); 
        virtual ~StickInputComponent();

        void update() override;
        void handleEvent() override;
    private:
        bool _isBallPicked; // booleano de si se ha pickeado la bola.

        Entity* _b; // entidad bola.
        ITransform* _bTransform; // transform de la bola
        //Entity* _palo; // referencia al palo.

        // Cosas de la circunferencia (area).
        double _radius; // radio.
        Vector2D _center; // centro.
    };
}