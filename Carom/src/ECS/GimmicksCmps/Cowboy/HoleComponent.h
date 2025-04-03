#pragma once

#include "ForceAreaComponent.h"
#include "RenderTextureComponent.h"


using isInsideField = bool;

    // Component that captures a single body
class HoleComponent : public ForceAreaComponent
{
protected:
    entity_t _contextEntt;
    RigidBodyComponent* _contextRB;
    RenderTextureComponent* _contextRender;

    bool _isEmpty;
    float _maxVelocityToFall;
    float _maxDistToFall;
    
public:
    __CMPID_DECL__(cmp::HOLE);

    HoleComponent(entity_t ent, float magnitude);
    ~HoleComponent() {}

    virtual void onTriggerEnter(entity_t other) override;
    virtual void onTriggerExit(entity_t other) override;
    b2Vec2 calculateForceToApply(Vector2D distanceVec);
    virtual void update() override;

    void resetChanges();

protected:
    virtual void applyForce(entity_t e) override;
    bool tryToCapture(float centersDist);
};
