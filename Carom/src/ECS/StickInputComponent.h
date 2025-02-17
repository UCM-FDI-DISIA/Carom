#pragma once
#include "Component.h"
#include <SDL.h>

class Entity;

namespace ecs{
    class StickInputComponent : public ecs::Component
    {
    public:
        StickInputComponent(Entity* e, SDL_Rect entityRect); 
        virtual ~StickInputComponent();

        void update() override;
        void handleEvent() override;

    private:
        SDL_Rect _rect; // rectangulo de la bola.
        Entity* _entity; // entidad bola.
        Entity* _palo; // referencia al palo.
    };
}