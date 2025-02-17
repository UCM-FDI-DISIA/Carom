#include "StickInputComponent.h"
#include "InputHandler.h"

namespace ecs { 

    // Hay que pasarle el rectangulo para la deteccion de clics.
    StickInputComponent::StickInputComponent(Entity* e, SDL_Rect entityRect) : Component(e){
        _entity = e;
        _rect = entityRect; // el rectángulo pasado de la bola lo usamos para handlearle los eventos.
    }

    StickInputComponent::~StickInputComponent(){
    }

    void StickInputComponent::update(){

    }

    void StickInputComponent::handleEvent(){
        auto& ihdlr = ih();

        // Si la bola se ha seleccionado.
        if(ihdlr.isBallSelectedUI(_rect)){
            std::cout << "The ball is selected." << std::endl;
        }

    }

}