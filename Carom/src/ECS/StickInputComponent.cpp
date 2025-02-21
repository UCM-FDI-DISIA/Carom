#include "StickInputComponent.h"
#include "InputHandler.h"

// El componente tiene que tener un init que inicialize el transform y el transform tiene que tener un getRect para pasarselo a este componente para que pueda funcionar.

/*
- La bola blanca tiene un radio para detectar el raton
- Una vez tu raton cumple estar centro de la circunferencia formada por ese radio y el centro de la bola aparece el palo colocado en base al vector formado por el raton y el centro de la bola
- En el momento que hagas click se queda fijado el vector de dirección y el palo se mueve hacia a lante o hacia atras según la proyeccion del ratón sobre el vector de disparo
- En el momento que se suelte el clic se llama a generar la fuerza sobre la bola en base al modulo entre el palo al centro de la bola
*/

namespace ecs { 

    // Hay que pasarle el rectangulo para la deteccion de clics.
    StickInputComponent::StickInputComponent(Entity* e, SDL_Rect entityRect) : Component(e){
        _entity = e;
        _rect = entityRect; // el rectángulo pasado de la bola lo usamos para handlearle los eventos.
        _isBallPicked = false; // inicialmente la bola está deseleccionada.
    }

    StickInputComponent::~StickInputComponent(){
    }

    void StickInputComponent::update(){
    }

    void StickInputComponent::handleEvent(){
        auto& ihdlr = ih();

        // Si la bola se ha seleccionado.
        if(ihdlr.isBallPickedIngame(_rect)){
            _isBallPicked = true;
            std::cout << "La bola se está seleccionando." << std::endl;
        }
        
        // Se suelta el raton mientras se estaba pickeando la bola.
        if(_isBallPicked && ihdlr.mouseButtonUpEvent()){
            _isBallPicked = false;
            std::cout << "La bola se ha soltado." << std::endl;
        }

        // Si la bola esta picked y mueves el ratón, se esta moviendo la bola.
        if(_isBallPicked && ihdlr.mouseMotionEvent()){
            std::cout << "Se está moviendo la bola" << std::endl;
        }
    }
}