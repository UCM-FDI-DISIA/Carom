#pragma once
#include "LogicComponent.h"
#include "RenderSpritesheetComponent.h"
#include "RigidBodyComponent.h"
#include <vector>

class BallRollerAnimatorComponent : public LogicComponent {
private:
    RenderSpritesheetComponent* _myRenderer;
    RigidBodyComponent* _myRigidbody;

    int _frameAmount;
    int _frameIndex;
    float _frameChangeThreshold;

    float _residualSpeed = .0;
public:
    __CMPID_DECL__(cmp::ANIMATOR);

    BallRollerAnimatorComponent(entity_t ent, float frameChangeThreshold = 1.0);
    ~BallRollerAnimatorComponent() {}

    void init() override;
    void update() override;
};