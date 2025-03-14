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

    bool _loop = false;

    bool _alive = true;

    //std::function<void> _onTweenExit;
public:
    Tween(float* start, float end, uint32_t duration, bool loop, Callback callback):_duration(duration){
        value = start;
        _startValue = *start;
        _endValue = end;
        _startTime = sdlutils().currRealTime();
        _alive = true;
        _loop = loop;
        _callback = callback;
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
//https://easings.net/#


class LinearTween: public Tween{
    public:
    inline LinearTween(float* start, float end, uint32_t duration,bool loop, Callback callback) : Tween(start, end, duration,loop, callback){}

    inline float easingFunction(float t) override{
        return t;
    }
};

class EaseInBackTween: public Tween{
    public:
    inline EaseInBackTween(float* start, float end, uint32_t duration, bool loop, Callback callback) : Tween(start, end, duration, loop, callback){}

    inline float easingFunction(float t) override{
        float c1 = 1.70158f;
        float c3 = c1 +1;
        return c3 * t * t * t - c1 * t * t;
    }
};

class EaseOutQuintTween: public Tween{
    public:
    inline EaseOutQuintTween(float* start, float end, uint32_t duration, bool loop, Callback callback) : Tween(start, end, duration,loop, callback){}

    inline float easingFunction(float t) override{
        return 1- pow(1-t, 5);
    }
};