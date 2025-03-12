#pragma once
#include <functional>
#include <cmath>
#include <algorithm>
#include "SDLUtils.h"

namespace tween{
    enum tweenType{
        LINEAR,
        EASE_IN_EXPO,
        EASE_OUT_QUINT,
        EASE_IN_BACK
    };
}

class Tween;
namespace ecs{
    class TransformComponent;
}

class TweenManager{
    std::vector<Tween*> _tweens;
    bool _paused;
public:
    TweenManager();
    ~TweenManager();
    void update();
    void removeTween(Tween* t);
    void pauseTweening();
    void resumeTweening();

    void easeValue(float* value, float finalValue, float duration, tween::tweenType type);
    void easePosition(ecs::TransformComponent* tr, Vector2D finalPos, float duration, tween::tweenType type);
    void easeRotation(ecs::TransformComponent* tr, float finalRot, float duration, tween::tweenType type);
};

