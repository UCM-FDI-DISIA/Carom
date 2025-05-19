#include "BallRollerAnimatorComponent.h"
#include <exception>
#include "Entity.h"
#include "SDLUtils.h"

BallRollerAnimatorComponent::BallRollerAnimatorComponent(entity_t ent,  float frameChangeThreshold ):
LogicComponent(ent),
_frameChangeThreshold(frameChangeThreshold),
_frameIndex(0) {}

void
BallRollerAnimatorComponent::init() {
    _myRenderer = _myEntity->getComponent<RenderSpritesheetComponent>();
    _myRenderer->setFrame(0);
    _frameAmount = _myRenderer->getFrameAmount();
    _myRigidbody = _myEntity->getComponent<RigidBodyComponent>();
}

void
BallRollerAnimatorComponent::update() {

    float vel = _myRigidbody->getVelocityMag();

    int a_framesToUpdate = vel + _residualSpeed / _frameChangeThreshold;
    _residualSpeed = (vel + _residualSpeed) - a_framesToUpdate * _frameChangeThreshold;

    if (a_framesToUpdate > 0)
    {
        if (a_framesToUpdate >= _frameAmount) a_framesToUpdate %= _frameAmount;

        int curframe = _myRenderer->getCurrentFrame();

        int a_destinyframe = curframe + a_framesToUpdate;
        if (a_destinyframe >= _frameAmount) a_destinyframe %= _frameAmount;

        _myRenderer->setFrame(a_destinyframe);
    }
}