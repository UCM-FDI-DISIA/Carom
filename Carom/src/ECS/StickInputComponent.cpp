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
        _center = _bTransform->getPosition(); // como la pos del transform es en el centro, el centro de la bola es el radius.
        _isInRadius = false; // inicialmente no se ha clicado el radio.
    }

    StickInputComponent::~StickInputComponent(){
    }

    void StickInputComponent::handleEvent()
    {
        auto& a_ih = ih(); // input handler.
        PhysicsConverter a_pu; // para meter2pixel converter.

        // --- Posiciones del raton (x, y).
        Sint32 a_mouseX = a_pu.pixel2meter(a_ih.getMousePos().first);
		Sint32 a_mouseY = a_pu.pixel2meter(a_ih.getMousePos().second);
        
        std::cout << "pos raton: (" << a_mouseX << ", " << a_mouseY << ")" << std::endl;
        std::cout << "centro bola: (" << _center.getX() << ", " << _center.getY() << ")" << std::endl;
        std::cout << "radio: " << _r << std::endl;

        // --- Circunferencia de centro (x0,y0) y radio r un punto (x,y) está en el interior de la circunferencia si ((x−x0)^2)+((y−y0)^2) < r^2.
        int a_x = std::pow(a_mouseX - _center.getX(), 2); // x: ((x−x0)^2)
        int a_y = std::pow(a_mouseY - _center.getY(), 2); // y: ((y−y0)^2)

        // --- (a+b < r^2) -> se cumple
        if(a_x + a_y < std::pow(_r, 2)){
            _isInRadius = true;
        } 
        else{
            _isInRadius = false;
        } 

        // Se apreta el mouse && en concreto el boton izquierdo (LEFT).
        bool a_leftClick =  a_ih.mouseButtonDownEvent() && a_ih.getMouseButtonState(a_ih.LEFT);

        // clic izquierdo + esta dentro del radio.
        if(a_leftClick && _isInRadius){
            s->active = true; // activas el palo.
            std::cout << "Se ha clicado DENTRO del radio." << std::endl;
        }
        else if(a_leftClick && !_isInRadius){
            s->active = false; // el palo permanece inactivo.
            std::cout << "Se ha clicado FUERA del radio." << std::endl;
        }
    }
}