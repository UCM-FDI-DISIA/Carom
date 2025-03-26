#pragma once
#include "SDLUtils.h"
#include "LogicComponent.h"
#include "ecs.h"
#include <functional>
namespace tween{
    enum tweenType{
        LINEAR,
        EASE_IN_EXPO,
        EASE_OUT_QUINT,
        EASE_IN_BACK,
        EASE_IN_OUT_CUBIC,
        EASE_OUT_ELASTIC
    };
}



class Tween;
class TransformComponent;

class TweenComponent :public LogicComponent{
    using Callback = std::function<void()>;

    std::vector<Tween*> _tweens;
    TransformComponent* _myTr;
    bool _paused;
public:
    __CMPID_DECL__(cmp::TWEEN);
    TweenComponent(entity_t ent);
    virtual ~TweenComponent();
    void init() override;
    void update() override;
    inline void setPause(bool b){_paused = b;}

    void easeValue(float* value, float finalValue, float duration, tween::tweenType type, bool loop = false , Callback callback = [](){});
    void easePosition(Vector2D finalPos, float duration, tween::tweenType type,bool loop = false, Callback callback = [](){});
    void easeRotation(float finalRot, float duration, tween::tweenType type,bool loop = false, Callback callback = [](){});

    void eraseAllTweens();
    inline bool isTweening() {return _tweens.size() >0;}
};



