#include "StickInputComponent.h"
#include "InputHandler.h"
#include "Entity.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "algorithm"
#include <cmath>
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
    StickInputComponent::StickInputComponent(Entity* e, float stickHeight) : HandleEventComponent(e), _stickHeight(stickHeight)
    {
    }
    
    // Rigidbody hereda de transform. Rigidbody es un transform.
    void StickInputComponent::init(){
        _ih = InputHandler::Instance();
        _myTransform = _myEntity->getComponent<TransformComponent>();
        _myRender = _myEntity->getComponent<RenderTextureComponent>();
    }

    void StickInputComponent::handleEvent()
    {
        //mousePos
        b2Vec2 _mousePos = PhysicsConverter::pixel2meter(_ih->getMousePos().first, _ih->getMousePos().second);
        
        std::cout <<_mousePos.x << " " << _mousePos.y << " ::: ";

        // centro de la bola
        b2Vec2 _center = _whiteBallRB->getPosition();

        // Vector direccion
        Vector2D dir = {_center.x - _mousePos.x, _center.y - _mousePos.y };
        Vector2D dirNormalized = dir.normalize();

        if (getMagFromMouseToCenter() > _maxRadiusToPull)
        {
            _mousePos.x = _center.x + (-dirNormalized.getX() * _maxRadiusToPull);
            _mousePos.y = _center.y + (-dirNormalized.getY() * _maxRadiusToPull);
        }

        std::cout <<_mousePos.x << " " << _mousePos.y << "\n";

        enableRender(true, _mousePos, dirNormalized);

        //std::cout << getMagFromMouseToCenter() << "\n";

        //si dentro del comportamiento se ha soltado el boton izquierdo del raton
        if(_ih->mouseButtonUpEvent() && _ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 0)
        {
            std::cout << "Dejado de arrastrar" << std::endl;

            if(!isMouseOnCircleRadius(_minRadiusToPull)){

                std::cout << "Golpe" << std::endl;
                if(dir.magnitude() > _maxRadiusToPull) dir = dir.normalize() * _maxRadiusToPull;

                float impulseMag = MAX_IMPULSE * (dir.magnitude() - _minRadiusToPull)/(_maxRadiusToPull - _minRadiusToPull); // normalizes [0,1]
                b2Vec2 impulseVec = {dirNormalized.getX() * impulseMag, dirNormalized.getY() * impulseMag};

                //aplicar fuerza a la bola con la direccion y la fuerza dependiendo de la distancia del raton
                _whiteBallRB->applyImpulseToCenter(impulseVec);

                std::cout << "mI " << impulseMag << "\n"; 
                std::cout << "impulso " << impulseVec.x << " " << impulseVec.y << "\n"; 
            }

            _active = false;
            enableRender(false, _mousePos, dirNormalized);
        }
    }

    bool StickInputComponent::isMouseOnCircleRadius(double r)
    {
        return getMagFromMouseToCenter() <= r;
    }

    float StickInputComponent::getMagFromMouseToCenter(){
        // --- Posiciones del raton (x, y).
        b2Vec2 _mousePos = PhysicsConverter::pixel2meter(_ih->getMousePos().first, _ih->getMousePos().second);
    
        // centro de la bola
        b2Vec2 _center = _whiteBallRB->getPosition();
        
        // Vector direccion
        Vector2D dir = {_mousePos.x - _center.x, _mousePos.y - _center.y};
    
        return dir.magnitude();
    }

    void StickInputComponent::enableRender(bool active, b2Vec2 _mousePos, Vector2D dirNormalized) {

        // enable render
        _myRender->setEnable(active);

        if (active) {

            float cosalpha = dirNormalized * Vector2D(1, 0);
            float sinalpha = dirNormalized * Vector2D(0, 1);

            float distX = PhysicsConverter::pixel2meter(_stickHeight/2) * cosalpha;
            float distY = PhysicsConverter::pixel2meter(_stickHeight/2) * sinalpha;

            float newRotation = rad2degrees(std::acos(cosalpha));
            if (sinalpha > 0) newRotation = -newRotation;
            newRotation = newRotation + 90.0f; // porque la imagen empiza de pie

            b2Vec2 newPos = {_mousePos.x - distX, _mousePos.y - distY};

            _myTransform->setPosition(newPos);
            _myTransform->setRotation(newRotation);
        }
    }

    double StickInputComponent::rad2degrees(double radians){
        return radians * (180.0f / M_PI);
    }

    void StickInputComponent::registerWhiteBall(entity_t wb)
    {
        _whiteBall = wb;
        _whiteBallRB = _whiteBall->getComponent<RigidBodyComponent>();
    }
}
