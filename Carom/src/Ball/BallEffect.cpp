#include "BallEffect.h"
#include "Entity.h"
#include "BallHandler.h"
#include "CaromScene.h"

void BallEffect::init()
{
    _scene = dynamic_cast<ecs::CaromScene*>(&_myEntity->getScene());
    assert(_scene != nullptr || "Se ha intentado agregar un componente de efecto en una escena que no es la de juego");
    _myEntity->getComponent<BallHandler>()->addEffect(this);
}

void BallEffect::onHit(ecs::entity_t ent)
{

}