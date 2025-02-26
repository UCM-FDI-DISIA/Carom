#pragma once
#include <vector>


class TweenSystem{

    enum TweenType{
        LINEAR,
        POW_IN,
        POW_OUT,
        POW_IN_OUT
    };

    struct Tween{
        float* initialValue;
        float finalValue;
        float time;
        float totalDistance;
        TweenType type;
        int loop;
    };

    std::vector<Tween> _currentTweens;
    void addTween(float* initialValue, float endValue,float time, TweenType type, int loop);
public:
    void updateValues();

    void removeTween(float* value);
    void linearTween(float* initialValue, float endValue, float time, int loop);
    void powerInTween(float* initialValue, float endValue, float time, int loop);
    void powerOutTween(float* initialValue, float endValue, float time, int loop);
    void powerInOutTween(float* initialValue, float endValue, float time, int loop);
};