#pragma once

#include "SDLUtils.h"
#include <functional>
#include <math.h>

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
    Callback _onUpdate;

    bool _loop = false;

    bool _alive = true;

    //std::function<void> _onTweenExit;
public:
    Tween(float* start, float end, uint32_t duration, bool loop, Callback callback, Callback onUpdate):_duration(duration){
        value = start;
        _startValue = *start;
        _endValue = end;
        _startTime = sdlutils().currRealTime();
        _alive = true;
        _loop = loop;
        _callback = callback;
        _onUpdate = onUpdate;
    };

    //aplica la interpolacion de la clase
    inline void update(){
        uint32_t currentTime =  sdlutils().currRealTime() - _startTime;

        //caso de que se haya pasado de tiempo, se setea a la posicion final

        if(currentTime > _duration) {
            _callback();
            *value = _endValue;

            //si el tween no se loopea, lo mata
            //si el tween se loopea, se cambian los parametros para que se hagan de forma inversa
            if(!_loop) _alive = false;
            else{
                float _final = _startValue;
                _startValue = _endValue;
                _endValue = _final;
                _startTime = sdlutils().currRealTime();
            }
            _onUpdate();
            return;
        }
        
        float t = (float)currentTime/(float)_duration;

        t = easingFunction(t);

        *value = interpolation(_startValue, _endValue, t);

        _onUpdate();
    };
    inline float interpolation(float a, float b, float t){ return a + t*(b-a); }
    virtual float easingFunction(float t) = 0;
    inline bool isAlive(){return _alive;}
    inline void setAlive(bool boolean) {_alive = boolean;}
};

//------------------------------------------DIFFERENT TYPES OF TWEENS--------------------------------
//https://easings.net/#


class LinearTween: public Tween{
    public:
    inline LinearTween(float* start, float end, uint32_t duration,bool loop, Callback callback, Callback onUpdate) : Tween(start, end, duration,loop, callback, onUpdate){}

    inline float easingFunction(float t) override{
        return t;
    }
};

class EaseInBackTween: public Tween{
    public:
    inline EaseInBackTween(float* start, float end, uint32_t duration, bool loop, Callback callback, Callback onUpdate) : Tween(start, end, duration,loop, callback, onUpdate){}

    inline float easingFunction(float t) override{
        float c1 = 1.70158f;
        float c3 = c1 +1;
        return c3 * t * t * t - c1 * t * t;
    }
};

class EaseInExponentialTween: public Tween{
    public:
    inline EaseInExponentialTween(float* start, float end, uint32_t duration, bool loop, Callback callback, Callback onUpdate) : Tween(start, end, duration,loop, callback, onUpdate){}

    inline float easingFunction(float t) override{
        if(t ==0) return 0;
        return pow(2, 10 * t - 10);
    }
};

class EaseOutQuintTween: public Tween{
    public:
    inline EaseOutQuintTween(float* start, float end, uint32_t duration, bool loop, Callback callback, Callback onUpdate) : Tween(start, end, duration,loop, callback, onUpdate){}

    inline float easingFunction(float t) override{
        return 1- pow(1-t, 5);
    }
};

class EaseInOutCubicTween: public Tween{
    public:
    inline EaseInOutCubicTween(float* start, float end, uint32_t duration, bool loop, Callback callback, Callback onUpdate) : Tween(start, end, duration,loop, callback, onUpdate){}

    inline float easingFunction(float t) override{
        if(t < 0.5) return 4 * t * t * t;
        return 1 - pow(-2 * t + 2, 3) / 2;
    }
    
};

class EaseOutElasticTween: public Tween{
    public:
    inline EaseOutElasticTween(float* start, float end, uint32_t duration, bool loop, Callback callback, Callback onUpdate) : Tween(start, end, duration,loop, callback, onUpdate){}

    inline float easingFunction(float t) override{
        if(t ==0) return 0;
        else if (t ==1) return 1;

        float c4 = (2 * M_PI) / 3;
        return pow(2, -10 * t) * sin((t * 10 - 0.75) * c4) + 1;
    }
};