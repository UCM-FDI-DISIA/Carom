#include "RenderArrayComponent.h"

#include "Entity.h"
#include "GameScene.h"
#include <exception>

#include <cmath>
#include <numbers>
#include "math.h"

RenderArrayComponent::RenderArrayComponent(entity_t ent,  Texture* tex, layerId_t renderLayer, 
    float scale, float gapScale)
: RenderComponent(ent, renderLayer),
_texture(tex),
_scale(scale),
_gapScale(gapScale),
_arrayLength(0)
{
    assert(tex != nullptr);

    _scaledWidth = tex->width() * scale;
}

void
RenderArrayComponent::init() {
    _myTransform = _myEntity->getTransform();
}

void
RenderArrayComponent::render() {

    if (_arrayLength > 0.0) 
    {

        int a_totalLength = _scaledWidth + _scaledWidth * _gapScale;

        while (a_totalLength <= _arrayLength) {
            _texture->render(
                _texture->getRect(), 
                getSectionRenderRect(a_totalLength),
                -_myTransform->getRotation()
            );

            a_totalLength += _scaledWidth + _scaledWidth * _gapScale;
        }
    }
}

SDL_Rect 
RenderArrayComponent::getSectionRenderRect(float currentLength) const
{
    b2Vec2 a_physicalPosition =  _myTransform->getPosition();

    auto [a_coordinateX, a_coordinateY] = 
        _myEntity->getScene().getCamera()->getRenderPos({a_physicalPosition.x, a_physicalPosition.y});

    a_coordinateX += cosf((_myTransform->getRotation())/180. * M_PI) * (currentLength - _scaledWidth/2);
    a_coordinateY += -sinf((_myTransform->getRotation())/180. * M_PI) * (currentLength - _scaledWidth/2);

    //Adapta el rect para que el objeto apareca en el centro de este
    a_coordinateX -= _scale * _texture->width() / 2;
    a_coordinateY -= _scale * _texture->height() / 2;

    return {
        a_coordinateX, 
        a_coordinateY, 
        static_cast<int>(_scaledWidth), 
        static_cast<int>(_texture->height() * _scale)
    };
}

void
RenderArrayComponent::setLength(float length)
{
    if (length >= 0.) _arrayLength = length;
}

SDL_Rect 
RenderArrayComponent::getRenderRect() const
{
    b2Vec2 physicalPosition = _myTransform->getPosition();
    //Obtiene la posición de pantalla a partir de la posición física para renderizar la textura
    auto [coordinateX, coordinateY] = 
        _myEntity->getScene().getCamera()->getRenderPos({physicalPosition.x, physicalPosition.y});
    
    //Adapta el rect para que el objeto apareca en el centro de este
    coordinateX -= _scale * _texture->width() / 2;
    coordinateY -= _scale * _arrayLength / 2;

    SDL_Rect dest = {coordinateX, coordinateY, static_cast<int>(_texture->width() * _scale), static_cast<int>(_arrayLength * _scale)};

    return dest;
}