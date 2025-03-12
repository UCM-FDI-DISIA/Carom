#pragma once
#include <functional>
#include <cmath>
#include <algorithm>
#include "SDLUtils.h"

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

    void linearTransformMovement(ecs::TransformComponent* tr, Vector2D finalPos, float duration);
    void easeInBackTransformMovement(ecs::TransformComponent* tr, Vector2D finalPos, float duration);
};