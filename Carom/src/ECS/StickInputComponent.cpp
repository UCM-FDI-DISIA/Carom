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
    StickInputComponent::StickInputComponent(Entity* e, ITransform* t) : HandleEventComponent(e){
        _b = e;
        _bTransform = t;
        _isBallPicked = false; // inicialmente la bola está deseleccionada.
        _r = (_bTransform->getScale().x/2) + 4.0f; // no importaria si fuese x o y, porque la bola es redonda por todos lados.
        _center = _bTransform->getPosition(); // como la pos del transform es en el centro, el centro de la bola es el radius.>
    }

    StickInputComponent::~StickInputComponent(){
    }

    void StickInputComponent::init()
    {
    }

    void StickInputComponent::handleEvent()
    {
        // NOTA: pasar luego todas estas variables al h para que no sean auxiliares.
        auto& a_ih = ih();
        PhysicsConverter a_pu; // para meter2pixel converter.
        Sint32 a_mouseX = a_pu.pixel2meter(a_ih.getMousePos().first);
		Sint32 a_mouseY = a_pu.pixel2meter(a_ih.getMousePos().second);
        
        bool a_isInRadius; // booleano para saber si esta dentro del radio.
        
        //std::cout << "pos raton: (" << a_mouseX << ", " << a_mouseY << ")" << std::endl;
       // std::cout << "centro bola: (" << _center.getX() << ", " << _center.getY() << ")" << std::endl;
        //std::cout << "radio: " << _r << std::endl;

        // ---- Circunferencia de centro (x0,y0) y radio r un punto (x,y) está en el interior de la circunferencia si ((x−x0)^2)+((y−y0)^2) < r^2.
        int a_x = std::pow(a_mouseX - _center.getX(), 2); // x: ((x−x0)^2)
        int a_y = std::pow(a_mouseY - _center.getY(), 2); // y: ((y−y0)^2)


        // ---- (a+b < r^2) -> se cumple
        if(a_x + a_y < std::pow(_r, 2)) a_isInRadius = true;
        else a_isInRadius = false;

        if(a_ih.mouseButtonDownEvent()  	       // se apreta el mouse.
			&& a_ih.getMouseButtonState(a_ih.LEFT) // en concreto el boton izquierdo.
			&& a_isInRadius){                      // y esta dentro del radio.
                std::cout << "Se ha clicado dentro del radio" << std::endl;
        }
        else if(a_ih.mouseButtonDownEvent() 
        && a_ih.getMouseButtonState(a_ih.LEFT)
        && !a_isInRadius){
            std::cout << "Se ha clicado fuera del radio" << std::endl;
        }
    }
}