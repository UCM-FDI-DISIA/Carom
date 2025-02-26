#include "StickInputComponent.h"
#include "Entity.h"
#include "RigidBodyComponent.h"


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
        _b = e;
        _isBallPicked = false; // inicialmente la bola está deseleccionada.
        _isInRadius = false; // inicialmente no se ha clicado el radio.
    }
    
    StickInputComponent::~StickInputComponent(){
        
    }
    
    // Rigidbody hereda de transform. Rigidbody es un transform.
    void StickInputComponent::init(){
        _bRB = _b->getComponent<RigidBodyComponent>(); 
        _r = (_bRB->getScale().x/2) + 4.0f; // no importaria si fuese x o y, porque la bola es redonda por todos lados.
        _center = _bRB->getPosition(); // como la pos del transform es en el centro, el centro de la bola es el radius.
        _maxR = _r + 3.0f; 
    }

    void StickInputComponent::handleEvent()
    {
        auto& a_ih = ih(); // input handler.
        PhysicsConverter a_pu; // para meter2pixel converter.

        // actualiza la posicion del centro de la bola.
        _center = _bRB->getPosition();

        _isInRadius = isOnCircleRadius(a_ih, a_pu, _r);
        _isInMaxRadius = isOnCircleRadius(a_ih, a_pu, _maxR);

        // si se clica en el radio y no se levanta el raton izquierdo, es que se esta seleccionando.
        if(_isInRadius && a_ih.mouseButtonDownEvent() && a_ih.getMouseButtonState(a_ih.LEFT)){
            _isBallPicked = true;
            std::cout << "Se esta SELECCIONANDO la bola" << std::endl;
        }
        // si se había pickeado la bola y se levanta el raton...
        else if(_isBallPicked && a_ih.mouseButtonUpEvent()){
            _isBallPicked = false;
        
            // si se suelta dentro del radio permitido...
            if(_isInMaxRadius){
                std::cout << "Se ha SOLTADO la bola dentro del RADIO PERMITIDO." << std::endl;

                /*
                Nota de Carmen: la idea de esto es pillar el punto donde se hace clic al principio y luego al soltar pillar el releasePoint, y 
                haciendo la resta se saca el vector dirección para aplicarselo a la bola (para que se mueva en dicha dirección), con una fuerza determinada, según cuánto se haya
                alejado del clickPoint.
                
                Vector2D clickPoint; // posicion donde se clica.
                Vector2D releasePoint; // posicion donde se suelta.
                Vector2D v = clickPoint - releasePoint;
                auto vx = v.getX();
                auto vy = v.getY();
                */

                
                
                // Condicion de si esta moviendose no puede lanzar la bola de nuevo. Solo puedes lanzar el impulso si no se mueve.
                if (b2Body_GetLinearVelocity( _bRB->getB2Body()).x == 0 && b2Body_GetLinearVelocity( _bRB->getB2Body()).y == 0){
                    _bRB->applyImpulseToCenter({10, 0}); // (10, 0), por ejemplo
                }
            } 
            else std::cout << "Se ha SOLTADO la bola FUERA del RADIO PERMITIDO." << std::endl;
            
            // !!!! al soltar se aplicaria la fuerza del palo.

        }
    }
    
    bool StickInputComponent::isOnCircleRadius(InputHandler& ih, PhysicsConverter pc, double r)
    {
        // --- Posiciones del raton (x, y).
        Sint32 a_mouseX = pc.pixel2meter(ih.getMousePos().first);
		Sint32 a_mouseY = pc.pixel2meter(ih.getMousePos().second);
        
        //std::cout << "pos raton: (" << a_mouseX << ", " << a_mouseY << ")" << std::endl;
        //std::cout << "centro bola: (" << _center.getX() << ", " << _center.getY() << ")" << std::endl;
        //std::cout << "radio: " << _r << std::endl;

        // --- Circunferencia de centro (x0,y0) y radio r un punto (x,y) está en el interior de la circunferencia si ((x−x0)^2)+((y−y0)^2) < r^2.
        int a_x = std::pow(a_mouseX - _center.getX(), 2); // x: ((x−x0)^2)
        int a_y = std::pow(a_mouseY - _center.getY(), 2); // y: ((y−y0)^2)

        // --- (a+b < r^2) -> se cumple
        return a_x + a_y < std::pow(r, 2);
    }
}