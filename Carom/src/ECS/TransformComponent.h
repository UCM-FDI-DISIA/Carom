#pragma once

#include <box2d/box2d.h>
#include "ecs.h"
#include "Vector2D.h"

#include "InfoComponent.h"
#include "ITransform.h"
#include "RigidBodyComponent.h"
#include "Entity.h"
#include "TweenComponent.h"


class TransformComponent : public InfoComponent, public ITransform{

    b2Vec2 _position;
    Scale _scale;
    float _rotation; //In radians

    //basicamente para que el tween pueda cambiar la posicion
    friend TweenComponent;
public:
    __CMPID_DECL__(cmp::TRANSFORM);

    TransformComponent(Entity* ent, const b2Vec2& pos);
    virtual ~TransformComponent(){}

    // Getters
    inline b2Vec2 getPosition() const override {return _position;}
    inline Scale getScale() const override {return _scale;}
    inline double getRotation() const override {return _rotation;}

    // Setters
    inline void setPosition(const b2Vec2& newPos) override {_position = newPos;}
    inline void setScale(const Scale& newScale) override {_scale = newScale;}
    inline void setRotation(const double& newRot) override {_rotation = newRot;}

};