#pragma once

#include <box2d/box2d.h>

/// @brief
///     Interfaz para todos los transform, cualquier componente que sea un transform
///     debe heredar de esta clase por cuestiones de polimorfismo.
class ITransform {
    public:

        struct Scale{
            double x;
            double y;
        };

        inline ITransform(){}
        virtual inline ~ITransform(){}

        // Getters
        virtual b2Vec2 getPosition() const = 0;
        virtual Scale getScale() const = 0;
        virtual double getRotation() const = 0;

        // Setters (no estoy seguro de si los setters deberían estar en la interfaz)
        virtual void setPosition(const b2Vec2& newPos) = 0;
        virtual void setScale(const Scale& newScale) = 0;
        virtual void setRotation(const double& newRot) = 0;
};