#include "StickInputComponent.h"
#include "InputHandler.h"
#include "Entity.h"
#include "RigidBodyComponent.h"
#include "algorithm"
#include "GameScene.h"
#include "ecs_defs.h"


// El componente tiene que tener un init que inicialize el transform y el transform tiene que tener un getRect para pasarselo a este componente para que pueda funcionar.

/*
- La bola blanca tiene un radio para detectar el raton
- Una vez tu raton cumple estar centro de la circunferencia formada por ese radio y el centro de la bola aparece el palo colocado en base al vector formado por el raton y el centro de la bola
- En el momento que hagas click se queda fijado el vector de dirección y el palo se mueve hacia a lante o hacia atras según la proyeccion del ratón sobre el vector de disparo
- En el momento que se suelte el clic se llama a generar la fuerza sobre la bola en base al modulo entre el palo al centro de la bola
*/

namespace ecs { 

    // Hay que pasarle el rectangulo para la deteccion de clics.
    StickInputComponent::StickInputComponent(Entity* e) : HandleEventComponent(e){
    }
    
    // Rigidbody hereda de transform. Rigidbody es un transform.
    void StickInputComponent::init(){
        _ih = InputHandler::Instance();
    }

    void StickInputComponent::handleEvent()
    {
        if(_behaviourEnabled){
            //si dentro del comportamiento se ha soltado el boton izquierdo del raton
            if(_ih->mouseButtonUpEvent() && _ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)){
                std::cout << "Dejado de arrastrar" << std::endl;
                _behaviourEnabled = false;
            }
        }
    }
    
    bool StickInputComponent::isOnCircleRadius(double r)
    {
        // --- Posiciones del raton (x, y).
        Sint32 a_mouseX = _ih->getMousePos().first;
		Sint32 a_mouseY = _ih->getMousePos().second;

        // centro de la bola
        b2Vec2 _center = _myEntity->getScene().getEntitiesOfGroup(grp::WHITEBALL)[0]->getTransform()->getPosition();
        
        // Vector direccion
        Vector2D dir = {a_mouseX - _center.x, a_mouseY - _center.y};
        // Magnitud
        float dirMag = std::sqrt(std::pow(dir.getX(), 2) + std::pow(dir.getY(), 2));

        return dirMag <= r;
    }
}