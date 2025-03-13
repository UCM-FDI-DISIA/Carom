#pragma once

#include "SDLUtils.h"
#include <functional>

class TweenComponent;
using Callback = std::function<void()>;
class Tween{
    protected:
    float _startValue;
    float* value;
    float _endValue;
    uint32_t _duration;
    uint32_t _startTime;
    
    Callback _callback;

    bool _alive = true;

    //std::function<void> _onTweenExit;
public:
    Tween(float* start, float end, uint32_t duration, Callback callback):_duration(duration){
        value = start;
        _startValue = *start;
        _endValue = end;
        _startTime = sdlutils().currRealTime();
        _alive = true;
        _callback = callback;
    };

    inline void update(){
        uint32_t currentTime =  sdlutils().currRealTime() - _startTime;
        if(currentTime > _duration) {
            _callback();
            _alive = false;
            *value = _endValue;
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
    inline LinearTween(float* start, float end, uint32_t duration, Callback callback) : Tween(start, end, duration, callback){}

    inline float easingFunction(float t) override{
        return t;
    }
};

class EaseInBackTween: public Tween{
    public:
    inline EaseInBackTween(float* start, float end, uint32_t duration, Callback callback) : Tween(start, end, duration, callback){}

    inline float easingFunction(float t) override{
        float c1 = 1.70158f;
        float c3 = c1 +1;
        return c3 * t * t * t - c1 * t * t;
    }
};

class EaseOutQuintTween: public Tween{
    public:
    inline EaseOutQuintTween(float* start, float end, uint32_t duration, Callback callback) : Tween(start, end, duration, callback){}

    inline float easingFunction(float t) override{
        float c1 = 1.70158f;
        float c3 = c1 +1;
        return c3 * t * t * t - c1 * t * t;
    }
};