#pragma once
#include "SDLUtils.h"
#include <functional>

class TweenManager;

class Tween{
    float _startValue;
    float* value;
    float _endValue;
    uint32_t _duration;
    uint32_t _startTime;

    bool _alive = true;

    //std::function<void> _onTweenExit;
    TweenManager* _manager;
public:
    Tween(TweenManager* manager, float* start, float end, uint32_t duration): _manager(manager), _duration(duration){
        value = start;
        _startValue = *start;
        _endValue = end;
        _startTime = sdlutils().currRealTime();
        _alive = true;
    };

    inline void update(){
        uint32_t currentTime =  sdlutils().currRealTime() - _startTime;
        if(currentTime > _duration) {
            //_onTweenExit;
            _alive = false;
            return;
        }
        
        float t = (float)currentTime/(float)_duration;

        t = easingFunction(t);

        *value = interpolation(_startValue, _endValue, t);
    };
    inline float interpolation(float a, float b, float t){ return a + t*(b-a); }
    virtual float easingFunction(float t) = 0;
    inline bool isAlive(){return _alive;}
    inline void setAlive(bool boolean) {_alive = boolean;}
};

//------------------------------------------DIFFERENT TYPES OF TWEENS--------------------------------

class LinearTween: public Tween{
    public:
    inline LinearTween(TweenManager* manager, float* start, float end, uint32_t duration) : Tween(manager, start, end, duration){}

    inline float easingFunction(float t) override{
        return t;
    }
};

class EaseInBackTween: public Tween{
    public:
    inline EaseInBackTween(TweenManager* manager, float* start, float end, uint32_t duration) : Tween(manager, start, end, duration){}

    inline float easingFunction(float t) override{
        float c1 = 1.70158f;
        float c3 = c1 +1;
        return c3 * t * t * t - c1 * t * t;
    }
};