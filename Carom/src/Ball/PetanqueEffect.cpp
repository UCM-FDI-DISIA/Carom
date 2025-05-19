#include "PetanqueEffect.h"
#include "Entity.h"
#include "GameScene.h"
#include "BallHandler.h"
#include "math.h"

void PetanqueEffect::init()
{
    BallEffect::init();
}

//Se ejecuta al final del tiro, se calcula la distancia entre la bola blanca y la bola con el efecto
// y se multiplica la puntuación por 2 * (1 - (distancia / MAX_DISTANCE)) para que cuanto más cerca esté de la bola blanca
// más se multiplique la puntuación
void PetanqueEffect::onStrikeEnd()
{
    entity_t _whiteBall = _myEntity->getScene().getEntitiesOfGroup(grp::WHITEBALL)[0];
    float distance = b2Distance(_myEntity->getTransform()->getPosition(), _whiteBall->getTransform()->getPosition());
    _handler->multScore(b2ClampFloat(2 * (1 - b2ClampFloat((distance/ MAX_DISTANCE), 0, 1)), 1, 2) * _handler->getMult());
}