#include "BallEffect.h"

#include "Entity.h"
#include "BallHandler.h"
#include "CaromScene.h"

namespace ecs {

    void BallEffect::init()
    {
        assert(_myEntity->tryGetComponent<BallHandler>() || "Se ha intentado añadir un efecto a una entidad sin administrador de efectos");
        _handler = _myEntity->getComponent<BallHandler>();
        _handler->addEffect(this);
    }
}
