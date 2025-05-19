#include "BallEffect.h"
#include "Entity.h"
#include "BallHandler.h"
#include "CaromScene.h"

//Se comprueba que la entidad tiene un administrador de efectos y en caso de tenerlo se le añade el efecto
//en caso contrario peta como Itadori
void BallEffect::init()
{
    assert(_myEntity->tryGetComponent<BallHandler>() && "Se ha intentado añadir un efecto a una entidad sin administrador de efectos");
    _handler = _myEntity->getComponent<BallHandler>();

    // _handler->addEffect(this);
}

BallEffect::~BallEffect(){
    
}