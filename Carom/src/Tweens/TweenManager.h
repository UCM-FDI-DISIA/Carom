#pragma once
#include <functional>
#include <cmath>
#include <algorithm>
#include "SDLUtils.h"

class Tween;

class TweenManager{
    std::vector<Tween*> _tweens;
    bool _paused;
public:
    TweenManager();
    void update();
    void removeTween(Tween* t);
    void pauseTweening();
    void resumeTweening();
};