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


class b2Vec2;
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
    //Pausa/despausa los tweens
    inline void setPause(bool b){_paused = b;}

    //Interpolacion linear de un valor por referencia
    //@param value Valor inicial, y que se va a actualizar constantemente
    //@param finalValue Valor final que va a tomar value
    //@param duration Duracion de la interpolacion
    //@param type Tipo de interpolacion 
    //@param loop Repeticion en bucle de la misma interpolacion, invirtiendose al alcanzar el final
    //@param callback Callback que se ejecuta al alcanzar el final
    //@param onUpdate Callback que se ejecuta en cada iteracion de update()
    void easeValue(float* value, float finalValue, float duration, tween::tweenType type, bool loop = false , Callback callback = [](){}, Callback onUpdate = [](){});
    
    //Interpolacion linear de la posicion de la entidad
    //@param finalPos Valor final que va a tomar la posicion de la entidad
    //@param duration Duracion de la interpolacion
    //@param type Tipo de interpolacion
    //@param loop Repeticion en bucle de la misma interpolacion, invirtiendose al alcanzar el final
    //@param callback Callback que se ejecuta al alcanzar el final
    //@param onUpdate Callback que se ejecuta en cada iteracion de update()
    void easePosition(b2Vec2 finalPos, float duration, tween::tweenType type,bool loop = false, Callback callback = [](){}, Callback onUpdate= [](){});
    
    //Interpolacion linear de la rotacion de la entidad
    //@param finalRot Valor final que va a tomar la rotacion de la entidad
    //@param duration Duracion de la interpolacion
    //@param type Tipo de interpolacion
    //@param loop Repeticion en bucle de la misma interpolacion, invirtiendose al alcanzar el final
    //@param callback Callback que se ejecuta al alcanzar el final
    //@param onUpdate Callback que se ejecuta en cada iteracion de update()
    void easeRotation(float finalRot, float duration, tween::tweenType type,bool loop = false, Callback callback = [](){}); 

    //Interpolacion linear de la rotacion de la entidad
    //@param finalRot Valor final que va a tomar la rotacion de la entidad
    //@param pivotPoint Punto de pivote para la rotacion
    //@param duration Duracion de la interpolacion
    //@param type Tipo de interpolacion
    //@param loop Repeticion en bucle de la misma interpolacion, invirtiendose al alcanzar el final
    //@param callback Callback que se ejecuta al alcanzar el final
    //@param onUpdate Callback que se ejecuta en cada iteracion de update()
    void easeRotation(float finalRot, b2Vec2 pivotPoint, float duration, tween::tweenType type,bool loop = false, Callback callback = [](){}); 

    //Interpolacion linear de la escala de la entidad
    //@param finalScale Valor final que va a tomar la escala de la entidad
    //@param duration Duracion de la interpolacion
    //@param type Tipo de interpolacion
    //@param loop Repeticion en bucle de la misma interpolacion, invirtiendose al alcanzar el final
    //@param callback Callback que se ejecuta al alcanzar el final
    //@param onUpdate Callback que se ejecuta en cada iteracion de update()
    void easeScale(float finalScale, float duration, tween::tweenType type,bool loop = false, Callback callback = [](){});

    //Borra todos los tweens en curso
    void eraseAllTweens();

    //Devuelve true si hay alguna interpolacion en curso
    inline bool isTweening() {return _tweens.size() >0;}
};
