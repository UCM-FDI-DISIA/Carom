#include "RenderArrayComponent.h"

#include "Entity.h"
#include "GameScene.h"
#include <exception>

RenderArrayComponent::RenderArrayComponent(entity_t ent,  Texture* tex, layerId_t renderLayer, 
    float scale, float gapScale)
: RenderComponent(ent, renderLayer),
_texture(tex),
_scale(scale),
_gapScale(gapScale),
_arrayLength(0)
{
    assert(tex != nullptr);

    _scaledHeight = tex->height() * scale;
}

void
RenderArrayComponent::init() {
    _myTransform = _myEntity->getTransform();
}

void
RenderArrayComponent::render() {

    if (_arrayLength > 0) {
        int a_totalLength = _scaledHeight;

        while (a_totalLength <= _arrayLength) {
            _texture->render(
                _texture->getRect(), 
                getSectionRenderRect(a_totalLength),
                _myTransform->getRotation()
            );

            a_totalLength += _scaledHeight + _scaledHeight * _gapScale;
        }
    }
}

SDL_Rect 
RenderArrayComponent::getSectionRenderRect(float currentLength) const
{
    b2Vec2 a_physicalPosition = _myTransform->getPosition();

    a_physicalPosition.x += cosf(_myTransform->getRotation()) * (currentLength - _scaledHeight/2);
    a_physicalPosition.x += sinf(_myTransform->getRotation()) * (currentLength - _scaledHeight/2);

    auto [a_coordinateX, a_coordinateY] = 
        _myEntity->getScene().getCamera()->getRenderPos({a_physicalPosition.x, a_physicalPosition.y});

    //Adapta el rect para que el objeto apareca en el centro de este
    a_coordinateX -= _scale * _texture->width() / 2;
    a_coordinateY -= _scale * _texture->height() / 2;

    return {
        a_coordinateX, 
        a_coordinateY, 
        static_cast<int>(_texture->width() * _scale), 
        static_cast<int>(_scaledHeight)
    };
}

SDL_Rect 
RenderArrayComponent::getRenderRect() const
{
    /*
    b2Vec2 physicalPosition = _myTransform->getPosition();
    //Obtiene la posición de pantalla a partir de la posición física para renderizar la textura
    auto [coordinateX, coordinateY] = 
        _myEntity->getScene().getCamera()->getRenderPos({physicalPosition.x, physicalPosition.y});
    
    //Adapta el rect para que el objeto apareca en el centro de este
    coordinateX -= _scale * _width / 2;
    coordinateY -= _scale * _height / 2;

    SDL_Rect dest = {coordinateX, coordinateY, static_cast<int>(_width * _scale), static_cast<int>(_height * _scale)};

    return dest;
    */

   return {0, 0, 0, 0};
}