#pragma once
#include "BallEffect.h"

class CristalEffect : public BallEffect
{
public:
    CristalEffect(ecs::entity_t ent) : BallEffect(ent) {
        _name = "Bola de Cristal";
        _description = "Extiende la línea de guía de la bola blanca hasta 3 rebotes si se está apuntando hacia ella";
    }
    ~CristalEffect() {}
    void onBeingTargeted() override;

    __CMPID_DECL__(ecs::cmp::CRISTAL_EFFECT);
    ecs::cmpId_t getEffectId() {return ecs::cmp::CRISTAL_EFFECT;};
};