#pragma once
#include <functional>
#include <cmath>
#include <algorithm>

class Tween{
    float _startValue;
    float& value;
    float _endValue;
    int _duration;
    int _startTime;
    std::function<void> _onTweenExit;
public:
    inline void update(){
        /*
        currentTime = cronometro - startTime
        if(currentTime > duration) {
            killMe();
            _onTweenExit();
            return;
        }
        
        float t = currentTime/duration;

        t = easingFunction(t);

        value = interpolation(_startValue, _endValue, t);
        */
    };
    inline float interpolation(float a, float b, float t){ return a + t*(b-a); };
};