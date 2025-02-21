#pragma once
#include "Component.h"
#include <SDL.h>
#include "ecs.h"

class Entity;

namespace ecs{
    class StickInputComponent : public ecs::Component
    {
    public:
        __CMPID_DECL__(cmp::STICK_INPUT);

        StickInputComponent(Entity* e, SDL_Rect entityRect); 
        virtual ~StickInputComponent();

        void update() override;
        void handleEvent() override;

    private:
        bool _isBallPicked;
        SDL_Rect _rect; // rectangulo de la bola.
        Entity* _entity; // entidad bola.
        Entity* _palo; // referencia al palo.
    };
}