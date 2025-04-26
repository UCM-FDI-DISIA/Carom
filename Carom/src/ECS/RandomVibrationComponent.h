#pragma once
#include "LogicComponent.h"
#include "ecs.h"
#include "ITransform.h"
#include <functional>

class RandomVibrationComponent: public LogicComponent{
    float _intensity;
    float _speed;
    b2Vec2 _anchoredPosition;
    std::function<void()> nextRandomPos;
public:
    __CMPID_DECL__(cmp::RANDOM_VIBRATION);
    RandomVibrationComponent(entity_t e, float intensity, float speed);
    void init() override;
    void update() override{};
};