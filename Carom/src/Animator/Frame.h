#pragma once

#include "Texture.h"
#include "Vector2D.h"

#include "FrameAnimatorComponent.cpp"

#include <functional>

/// @brief Representa un fotograma de una animacion
class Frame {
public:
    /// @brief Constructor de frame
    /// @param frameDuration duracion del frame. 1 = 1000/60 milisegundos (1/60 segs)
    /// @param tex debe no ser nula
    /// @param scale 
    /// @param nextFrame puede ser nulo, significa que la animacion acaba
    /// @param enterCallback opcional
    /// @param exitCallback opcional
    Frame(Uint32 frameDuration, Texture* tex, float scale, Frame* nextFrame = nullptr, 
        std::function<void()> enterCallback = [] {}, std::function<void()> exitCallback = [] {});
    ~Frame() {}

    enum Animation {
        DEFAULT
    };

private:

    friend class ecs::FrameAnimatorComponent;

    /// @brief Tiempo en milisegundos que el fotograma está activo
    Uint32 _milliseconds;
    /// @brief Textura del frame
    Texture* _texture;
    /// @brief Escala del frame
    float _scale;

    /// @brief Callbacks a ejecutar al activar y desactivar el frame
    std::function<void()> _enterCallback;
    std::function<void()> _exitCallback;

    /// @brief Siguiente frame a activar, es como un sistema de nodos pero muy mierdoso, que los concentra
    Frame* _nextFrame = nullptr;
};