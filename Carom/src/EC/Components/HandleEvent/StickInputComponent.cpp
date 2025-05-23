#include "StickInputComponent.h"

#include "StickEffectComponent.h"
#include "InputHandler.h"
#include "Entity.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "RenderArrayComponent.h"
#include "CaromScene.h"
#include "ShadowComponent.h"
#include "algorithm"
#include <cmath>
#include "GameScene.h"
#include "ecs_defs.h"
#include "AudioManager.h"


// El componente tiene que tener un init que inicialize el transform y el transform tiene que tener un getRenderRect para pasarselo a este componente para que pueda funcionar.

/*
- La bola blanca tiene un radio para detectar el raton
- Una vez tu raton cumple estar centro de la circunferencia formada por ese radio y el centro de la bola aparece el palo colocado en base al vector formado por el raton y el centro de la bola
- En el momento que se suelte el clic se llama a generar la fuerza sobre la bola en base al modulo entre el palo al centro de la bola
*/

// Hay que pasarle el rectangulo para la deteccion de clics.
StickInputComponent::StickInputComponent(Entity* e) : HandleEventComponent(e), _myEffect(nullptr)
{ 
    _myCaromScene = dynamic_cast<CaromScene*>(&e->getScene());
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
    
    // Controls position and rotation of the transform
    transformControl(_mousePos, dir);

    // Controla posicion de la linea de apuntado y asigna longitud
    aimLineTransformControl(dir);
    
    //si dentro del comportamiento se ha soltado el boton izquierdo del raton
    if(_ih->mouseButtonUpEvent() && _ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) == 0)
    {
        if (_aimLine != nullptr)
        {
            _aimLine->getComponent<RenderArrayComponent>()->setLength(0.0);
        }

        if(!isMouseOnCircleRadius(_minRadiusToPull)){

            if(dir.magnitude() > _maxRadiusToPull) dir = dir.normalize() * _maxRadiusToPull;

            float impulseMag = MAX_IMPULSE * (dir.magnitude() - _minRadiusToPull)/(_maxRadiusToPull - _minRadiusToPull); // normalizes [0,1]
            b2Vec2 impulseVec = {dirNormalized.getX() * impulseMag, dirNormalized.getY() * impulseMag};
            

            //aplicar tween con callback al final
            TweenComponent* _tween = _myEntity->getComponent<TweenComponent>();
            Vector2D distance = dirNormalized * PhysicsConverter::pixel2meter(_myRender->getRenderRect().w)/2;
            float a_ballRadius = PhysicsConverter::pixel2meter(_whiteBall->getRenderer()->getRenderRect().w/2);
            _tween->easePosition({_center.x - distance.getX() - dirNormalized.getX() - a_ballRadius,
                                    _center.y - distance.getY() - dirNormalized.getY() - a_ballRadius},
                                    .08f, tween::EASE_IN_EXPO, false, [=](){
                                    //aplicar fuerza a la bola con la direccion y la fuerza dependiendo de la distancia del raton
                                    _whiteBallRB->applyImpulseToCenter(impulseVec);

                //aplicar el efecto del palo si lo tiene
                if(_myEffect != nullptr) _myEffect->applyEffect(_whiteBall);
                else AudioManager::Instance()->playSoundEfect("stick_hit");

                _hasShot = true; // ! hasShot

                _myEntity->getScene().getCamera()->shakeCamera(0.15f * impulseMag/MAX_IMPULSE, 0.3f, dirNormalized);
            });
        }
        
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

void StickInputComponent::setEnabled(bool state)
{
    _hasShot = false;
    _isEnable = state;
}

void StickInputComponent::transformControl(b2Vec2 _mousePos, Vector2D dir)
{

    float cosalpha = dir.normalize() * Vector2D(1, 0);
    float sinalpha = dir.normalize() * Vector2D(0, 1);

    Vector2D a_mousePos = {_mousePos.x, _mousePos.y};

    Vector2D a_ballCenter = { _whiteBall->getComponent<RigidBodyComponent>()->getPosition().x,
                                _whiteBall->getComponent<RigidBodyComponent>()->getPosition().y};
    float a_ballRadius = PhysicsConverter::pixel2meter(_whiteBall->getRenderer()->getRenderRect().w/2);
    float a_stickHeight = _myRender->getRenderRect().h;

    float distX = PhysicsConverter::pixel2meter(a_stickHeight/2) * cosalpha;
    float distY = PhysicsConverter::pixel2meter(a_stickHeight/2) * sinalpha;
    
    // when the mouse is inside the ball the stick won't put itself above it
    if (dir.magnitude() < a_ballRadius) {
        float a_offset = a_ballRadius - dir.magnitude();
        distX = (PhysicsConverter::pixel2meter(a_stickHeight/2) + a_offset) * cosalpha;
        distY = (PhysicsConverter::pixel2meter(a_stickHeight/2) + a_offset) * sinalpha;
    }

    float newRotation = rad2degrees(std::acos(cosalpha));
    if (sinalpha > 0) newRotation = -newRotation;
    newRotation = newRotation + 90.0f; // porque la imagen empieza de pie

    b2Vec2 newPos = {_mousePos.x - distX, _mousePos.y - distY};

    _myTransform->setPosition(newPos);
    _myTransform->setRotation(newRotation);

    _myEntity->getComponent<RenderTextureComponent>()->setEnabled(true);
    _myEntity->getComponent<ShadowComponent>()->setEnabled(true);
}

void StickInputComponent::aimLineTransformControl(Vector2D dir)
{
    if (_aimLine != nullptr && _myCaromScene != nullptr)
    {
        float a_cosalpha = dir.normalize() * Vector2D(1, 0);
        float a_sinalpha = dir.normalize() * Vector2D(0, 1);
    
        float a_ballRadius = 
            PhysicsConverter::pixel2meter(_whiteBall->getRenderer()->getRenderRect().w/2);
    
        b2Vec2 a_ballCenter = { _whiteBall->getComponent<RigidBodyComponent>()->getPosition().x,
            _whiteBall->getComponent<RigidBodyComponent>()->getPosition().y};
    
        b2Vec2 a_physical_lineStart = b2Vec2(a_ballCenter.x + a_cosalpha * a_ballRadius, 
            a_ballCenter.y + a_sinalpha * a_ballRadius);

        b2RayResult rayResult = _myCaromScene->castRayToWorld(a_ballCenter, b2Vec2((a_ballCenter.x + a_cosalpha * 100.f), 
            (a_ballCenter.y + a_sinalpha * 100.f)));

        // Si alguien pregunta por como va esta mierda, ya ni se como va, maldigo a la geometría

        _aimLine->getComponent<RenderArrayComponent>()->
            setLength(PhysicsConverter::meter2pixel(b2Length(rayResult.point - a_physical_lineStart)));
            
        _aimLine->getComponent<TransformComponent>()->setPosition(a_physical_lineStart);
        _aimLine->getComponent<TransformComponent>()->setRotation(rad2degrees(atan2(a_sinalpha, a_cosalpha)));
        
    }
}

double StickInputComponent::rad2degrees(double radians){
    return radians * (180.0f / M_PI);
}

void StickInputComponent::registerWhiteBall(entity_t wb)
{
    assert(wb != nullptr);
    _whiteBall = wb;
    _whiteBallRB = _whiteBall->getComponent<RigidBodyComponent>();
    _minRadiusToPull = PhysicsConverter::pixel2meter(_whiteBall->getRenderer()->getRenderRect().w/2);
}

void StickInputComponent::registerStickEffect(StickEffectComponent* effect) {
    _myEffect = effect;
}

void StickInputComponent:: registerAimLine(entity_t aL)
{
    _aimLine = aL;
}