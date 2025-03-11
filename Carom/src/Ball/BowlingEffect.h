#pragma once
#include "BallEffect.h"

class BowlingEffect : public BallEffect
{
private:
    static constexpr float DENSITY = 1.5f;
    static constexpr float FRICTION = 0.4f;
public:
    void init() override;
};