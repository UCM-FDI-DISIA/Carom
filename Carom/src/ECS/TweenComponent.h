#pragma once
#include "SDLUtils.h"
#include "LogicComponent.h"
#include "ecs.h"

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

    class TweenComponent :public LogicComponent{
        std::vector<Tween*> _tweens;
        TransformComponent* _myTr;
        bool _paused;
    public:
        __CMPID_DECL__(cmp::TWEEN);
        TweenComponent(entity_t ent);
        virtual ~TweenComponent();
        void init() override;
        void update() override;
        void pauseTweening();
        void resumeTweening();
    
        void easeValue(float* value, float finalValue, float duration, tween::tweenType type);
        void easePosition(Vector2D finalPos, float duration, tween::tweenType type);
        void easeRotation(float finalRot, float duration, tween::tweenType type);
    };
}



